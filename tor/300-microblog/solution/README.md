# 300 - Microblog (Solution)

## Finding the challenge

There's an onion address in the challenge description. Grab yourself a Tor browser and navigate to it!

## Solving the challenge

Once you visit the provided URL, you should see a sign in page for the BSides PDX CTF 2020 Microblog. Since registration appears to be open, go ahead and register yourself a new user and login.

Once you're logged in, you can see that it's similar to Twitter. You can post messages and they'll show up on the wall. You can try to put SQLi or XSS or whatever in your post, but if the challenge author didn't mess anything up, it should be fruitless. If you go to your profile, you should see an "Edit your profile" link. Going into that, there are a number of options. Changing your username and the data in the "About me" section shouldn't do anything (once again, assuming the challenge author didn't bugger up something).

However, there are two more interesting fields. One allows you to change your avatar by uploading an image, and the other allows you to point to a URL of an image for the server to grab. The image upload should be another dead end (say it with me everyone: assuming the challenge author didn't screw up). The URL field is the interesting one.

It only seems to take URLs that end in jpg or png. It also seems to fail if you give it a URL that ends in one of those extensions but is really something like a web shell. Come on, I know you tried it. Nice try. It seems to be doing some checking and verification of the file. So, let's stand up our own server and see what it's doing. I used the python script [found here](https://gist.github.com/phrawzty/62540f146ee5e74ea1ab) so that way we can see the headers as well. All the Tor challenges so far have had the flags in the headers, so it seems like a safe bet we'll need headers once again. If you do that, and point the Avatar url to it, you can see it first makes a HEAD request. If you actually point it at an image, the subsequent GET request contains the flag.

## Flag
`BSidesPDX{3veR_7r!ed_t0_sSrF_4n_0n!on?}`