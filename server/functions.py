import os
from keycodes import *


def extract_substring(string1, string2, string3):
    start_index = string1.find(string2) + len(string2)
    end_index = string1.find(string3)
    return string1[start_index:end_index]


def adbinput(command):
    os.system("./adb shell input keyevent " + command)


def adbinput_repeat(command, number):
    temp = "./adb shell \""
    for n in range(number):
        temp += "input keyevent " + command + "; "
    temp += "\""
    print(temp)
    os.system(temp)


def is_sleeping():
    line = os.popen("./adb shell dumpsys activity activities | grep -E -m 1 'isSleeping'").read()
    return line == "isSleeping=true"


def turn_on(movie):
    # turn it on
    adbinput(HOME)
    print("turned on TV")
    open_netflix(movie)


def is_netflix_open():
    current_focus = os.popen("./adb shell dumpsys window windows | grep -E 'mCurrentFocus'").read()
    return "netflix" in current_focus


def open_netflix(movie):
    adbinput(HOME)
    adbinput(DPAD_LEFT)
    adbinput(DPAD_CENTER)
    adbinput(DPAD_DOWN)
    adbinput(DPAD_CENTER)
    os.system("./adb shell input text \"netflix\"")
    adbinput(DPAD_DOWN)
    adbinput(DPAD_DOWN)
    adbinput(DPAD_CENTER)
    adbinput(DPAD_CENTER)

    # netflix is open
    print("opened netflix")
    start_movie(movie)


def is_movie_playing():
    line = os.popen("./adb shell dumpsys media_session | grep -m 1 \"state=PlaybackState\"").read()
    state = extract_substring(line, "{state=", ",")
    return state == "3" or "2" or "1"


def start_movie(movie_name):
    # get to search menu
    adbinput(BACK)
    adbinput(BACK)
    adbinput(BACK)
    adbinput(BACK)
    adbinput(BACK)
    adbinput(DPAD_LEFT)
    adbinput(DPAD_UP)
    adbinput(DPAD_UP)
    adbinput(DPAD_UP)
    adbinput(DPAD_DOWN)
    adbinput(DPAD_DOWN)
    adbinput(DPAD_CENTER)

    # in the search text bar
    # clear the search bar
    os.system("./adb shell input keyevent --longpress " + 50 * DELETE)

    # search
    os.system(f'./adb shell input text \"{movie_name}\"')
    adbinput(BACK)
    adbinput(BACK)
    adbinput(DPAD_RIGHT)
    adbinput(DPAD_RIGHT)
    adbinput(DPAD_RIGHT)
    adbinput(DPAD_RIGHT)
    adbinput(DPAD_RIGHT)
    adbinput(DPAD_RIGHT)
    adbinput(DPAD_CENTER)
    adbinput(DPAD_CENTER)
    print("started the movie")


def play_pause():
    adbinput(PLAY_PAUSE)
    print("play/paused the movie")
