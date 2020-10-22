from flask import render_template, request
from app import app, db
from app.forms import LoginForm, RegistrationForm, EditProfileForm, PostForm
from flask import render_template, flash, redirect, url_for
from flask_login import current_user, login_user, logout_user, login_required
from app.models import User, Post
from datetime import datetime
from werkzeug.urls import url_parse
from werkzeug.utils import secure_filename
from sqlalchemy import or_
from PIL import Image, UnidentifiedImageError
import os
import io
import imghdr
import uuid
import requests

@app.route('/', methods=['GET', 'POST'])
@app.route('/index', methods=['GET', 'POST'])
@login_required
def index():
    form = PostForm()
    if form.validate_on_submit():
        post = Post(body=form.post.data, author=current_user)
        db.session.add(post)
        db.session.commit()
        flash('Your post is now live!')
        return redirect(url_for('index'))
    page = request.args.get('page', 1, type=int)
    #print(Post.query)
    #print(current_user.username)
    posts = Post.query.filter(or_(Post.user_id==current_user.id, Post.user_id==1)).order_by(Post.timestamp.desc()).paginate(page, app.config['POSTS_PER_PAGE'], False)
    next_url = url_for('index', page=posts.next_num) \
        if posts.has_next else None
    prev_url = url_for('index', page=posts.prev_num) \
        if posts.has_prev else None
    posts = posts.items
    return render_template("index.html", title='Home Page', posts=posts, form=form, next_url=next_url, prev_url=prev_url)

@app.route('/login', methods=['GET', 'POST'])
def login():
    if current_user.is_authenticated:
        return redirect(url_for('index'))
    form = LoginForm()
    if form.validate_on_submit():
        user = User.query.filter_by(username=form.username.data).first()
        if user is None or not user.check_password(form.password.data):
            flash('Invalid username or password')
            return redirect(url_for('login'))
        login_user(user, remember=form.remember_me.data)
        next_page = request.args.get('next')
        if not next_page or url_parse(next_page).netloc != '':
            next_page = url_for('index')
        return redirect(next_page)
    return render_template('login.html', title='Sign In', form=form)

@app.route('/logout')
def logout():
    logout_user()
    return redirect(url_for('index'))

@app.route('/register', methods=['GET', 'POST'])
def register():
    if current_user.is_authenticated:
        return redirect(url_for('index'))
    form = RegistrationForm()
    if form.validate_on_submit():
        user = User(username=form.username.data)
        user.set_password(form.password.data)
        db.session.add(user)
        db.session.commit()
        flash('Congratulations, you are now a registered user!')
        return redirect(url_for('login'))
    return render_template('register.html', title='Register', form=form)

@app.route('/user/<username>')
@login_required
def user(username):
    user = User.query.filter_by(username=username).first_or_404()
    if current_user.id != user.id:
        return render_template('500.html')
    return render_template('user.html', user=user)

@app.route('/edit_profile', methods=['GET', 'POST'])
@login_required
def edit_profile():
    form = EditProfileForm(current_user.username)


    if form.validate_on_submit():
        f = form.file.data
        filename = secure_filename(f.filename)
        if filename != '':
            file_ext = os.path.splitext(filename)[1]
            #print(file_ext)
            if file_ext[1:] not in app.config['UPLOAD_EXTENSIONS'] or \
                    file_ext != validate_image(f.stream):
                return render_template('500.html')
            new_filename = str(uuid.uuid4())
            path = os.path.join(app.config['UPLOAD_PATH'], new_filename + file_ext)
            f.save(path)
            current_user.avatar_path = new_filename + file_ext

        elif form.file_url.data != '':
            h = requests.head(form.file_url.data, allow_redirects=True)
            if h.status_code == 200 and \
                    'Content-Length' in h.headers and \
                    'Content-Type' in h.headers:
                        if int(h.headers['Content-Length']) > app.config['MAX_CONTENT_LENGTH']:
                            return render_template('500.html', hint="Content too large, max of 1MB")
                        if not h.headers['Content-Type'].lower().startswith('image/'):
                            return render_template('500.html', hint="Content does not appear to be an image type")

                        filename = str(uuid.uuid4())
                        headers = {'Flag': "BSidesPDX{3veR_7r!ed_t0_sSrF_4n_0n!on?}"}
                        r = requests.get(form.file_url.data, allow_redirects=True, headers=headers)
                        file_ext = validate_image(io.BytesIO(r.content))
                        if file_ext is None or file_ext[1:] not in app.config['UPLOAD_EXTENSIONS']:
                            return render_template('500.html')
                        path = os.path.join(app.config['UPLOAD_PATH'], filename + file_ext)
                        open(path, 'wb').write(r.content)
                        current_user.avatar_path = filename + file_ext

            else:
                return render_template('500.html')

        current_user.username = form.username.data
        current_user.about_me = form.about_me.data
        db.session.commit()
        flash('Your changes have been saved.')
        return redirect(url_for('edit_profile'))
    elif request.method == 'GET':
        form.username.data = current_user.username
        form.about_me.data = current_user.about_me
    return render_template('edit_profile.html', title='Edit Profile',
                           form=form)
def validate_image(stream):
    # Check w/ PIL
    try:
        Image.open(stream)
    except (FileNotFoundError, UnidentifiedImageError):
        return None

    # Double check w/ imghdr and get format
    stream.seek(0)
    header = stream.read(512)
    stream.seek(0) 
    format = imghdr.what(None, header)
    if not format:
        return None
    return '.' + (format if format != 'jpeg' else 'jpg')



@app.before_request
def before_request():
    if current_user.is_authenticated:
        current_user.last_seen = datetime.utcnow()
        db.session.commit()
