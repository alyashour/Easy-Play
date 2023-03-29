from flask import Flask, render_template, request
from functions import *
from threading import Lock # so we dont get stupid multi functions
import os
import time


off_timer = time.time()
app = Flask(__name__)
ip = '192.168.0.197:5555'
os.chdir("platform-tools")  # nav to adb commands
fav_movie = "interstellar"
lock = Lock()


@app.route('/', methods=['GET'])
def index():
    return render_template('index.html')


@app.route('/save_input', methods=['POST'])
def save_input():
    input_text = request.form['text']
    # do something with the input_text variable, such as save it to a database
    print("New fav movie is: " + input_text)
    global fav_movie
    fav_movie = input_text
    return f'The input text is: {input_text}'


@app.route('/button')
def button():
    with lock:
        # adb commands
        print(os.getcwd())
        os.system("./adb connect " + ip)

        if is_sleeping():
            turn_on(fav_movie)
        elif not is_netflix_open():
            open_netflix(fav_movie)
        elif not is_movie_playing():
            start_movie(fav_movie)
        elif is_movie_playing():
            play_pause()
        else:
            print("something went wrong on button press")

        os.system("./adb disconnect " + ip)
    return 'play/paused'


@app.route('/checkwindow')
def check_window():
    os.system("./adb connect " + ip)
    os.system("./adb shell dumpsys window windows | grep -E 'mCurrentFocus'")
    os.system("./adb disconnect " + ip)
    return 'checked window'


@app.route('/checksleeping')
def check_sleeping():
    os.system("./adb connect " + ip)
    line = os.popen("./adb shell dumpsys activity activities | grep -E -m 1 'isSleeping'").read()
    os.system("./adb disconnect " + ip)
    return line


@app.route('/checkmovie')
def check_movie():
    os.system("./adb connect " + ip)
    line = os.popen("./adb shell dumpsys media_session | grep \"state=PlaybackState\"").read()
    os.system("./adb disconnect " + ip)
    return line



@app.route('/')
def hello():
    return 'Hello world!'
