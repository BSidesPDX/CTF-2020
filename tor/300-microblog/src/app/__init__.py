from flask import Flask
from config import Config
from flask_sqlalchemy import SQLAlchemy
from flask_migrate import Migrate
from flask_login import LoginManager
from flask_bootstrap import Bootstrap

app = Flask(__name__)
app.config.from_object(Config)
db = SQLAlchemy(app)
migrate = Migrate(app, db)
login = LoginManager(app)
login.login_view = 'login'
bootstrap = Bootstrap(app)


from app import routes, models, errors, db
from app.models import User, Post

# Had to comment this out because of weirdness w/ multiple workers on start
# Just saying screw this and copying a known good db at docker entrypoint
'''
@app.before_first_request
def setup():
    meta = db.metadata
    for table in reversed(meta.sorted_tables):
        print('Clear table %s' % table)
        db.session.execute(table.delete())
    db.session.commit()

    _init_fake_data()
'''

def _init_fake_data():
    u = User(username='fdcarl')
    u.set_password('fdcarl')
    db.session.add(u)

    p = Post(body="Welcome to the BSides PDX CTF microblogging platform!", author=u)
    db.session.add(p)

    u = User(username='susan')
    u.set_password('susan')
    db.session.add(u)


    p = Post(body="Testing", author=u)
    db.session.add(p)

    db.session.commit()
