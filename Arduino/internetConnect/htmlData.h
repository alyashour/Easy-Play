//#include <Arduino.h>

char htmlData2[] = R"(
<form action="/" method="get" enctype="application/x-www-form-urlencoded">
  <div>
    Form below: <br>
    Please enter the network username: <input type="text" id="username" name="username" size="10"><br>
    Please enter the network password: <input type="password" id="password" name="password" size="10"><br>
    <input type="submit" value="Send" />
  </div>
</form>
)";

char htmlData3[] = R"(
<!DOCTYPE html>
<html>
  <head>
    <title>Internet Login Information</title>
    <style>
      body {
        font-family: Candara;
        margin: 0;
        padding: 0;
      }
      .container {
        margin: 50px auto;
        max-width: 600px;
        padding: 20px;
        background-color: #f1f1f1;
        border-radius: 10px;
        box-shadow: 0px 0px 10px rgba(0, 0, 0, 0.2);
      }
      h1 {
        text-align: left;
      }
      form {
        display: flex;
        flex-direction: column;
      }
      label {
        margin-top: 10px;
      }
      input[type="text"],
      input[type="password"] {
        padding: 10px;
        border: none;
        border-radius: 5px;
        background-color: #ffffff;
        box-shadow: 0px 0px 5px rgba(0, 0, 0, 0.2);
        margin-bottom: 20px;
        font-size: 16px;
      }
      button[type="submit"] {
        background-color: #4CAF50;
        color: #ffffff;
        padding: 10px;
        border: none;
        border-radius: 5px;
        font-size: 16px;
        cursor: pointer;
        transition: background-color 0.3s ease-in-out;
      }
      button[type="submit"]:hover {
        background-color: #3e8e41;
      }
      
      button[type="confirm"] {
        background-color: gray;
        color: #ffffff;
        padding: 10px;
        border: none;
        border-radius: 5px;
        font-size: 16px;
        cursor: pointer;
        transition: background-color 0.3s ease-in-out;
      }
      button[type="confirm"]:hover {
        background-color: #007bff;
      }
      
      p {
        margin: 10px 0;
      }
      span {
        font-weight: bold;
      }

    </style>
  </head>
  <body>
    <div class="container">
      <h1>Hello!</h1>
      This is the button,<br>
      To work we need to connect to your home internet.<br>
      Please enter your network SSID and password below.
      
    <form>
        <label for="username">Network SSID:</label>
        <input type="text" id="username" name="username">
        <label for="password">Password:</label>
        <input type="password" id="password" name="password">
        <button type = "submit" id="save-btn">Save</button>
    </form>
    
    <form>
    <h2>Current username and Password</h2>
      <p>Saved Username: <span id="savedUsername">exampleUsername</span></p>
      <p>Saved Password: <span id="savedPassword">examplePassword</span></p>
      <button type = "confirm" id="confirm-btn">Confirm</button>
    </form>
    </div>
  </body>
</html>
)";

char htmlData[] = R"(
<!DOCTYPE html>
<html>
  <head>
    <title>Internet Login Information</title>
    <style>
      body {
        font-family: Candara, sans-serif;
        margin: 0;
        padding: 0;
        background-color: #f7f7f7;
      }
      
      .container {
        margin: 50px auto;
        max-width: 600px;
        padding: 20px;
        background-color: #fff;
        border-radius: 10px;
        box-shadow: 0px 0px 10px rgba(0, 0, 0, 0.2);
      }
      
      h1 {
        font-size: 32px;
        text-align: center;
        margin-bottom: 20px;
        color: #333;
      }
      
      h2 {
        font-size: 24px;
        margin-bottom: 10px;
        color: #555;
      }
      
      form {
        display: flex;
        flex-direction: column;
        margin-bottom: 20px;
      }
      
      label {
        margin-top: 10px;
        font-size: 16px;
        color: #555;
      }
      
      input[type="text"],
      input[type="password"] {
        padding: 10px;
        border: none;
        border-radius: 5px;
        background-color: #f7f7f7;
        box-shadow: 0px 0px 5px rgba(0, 0, 0, 0.2);
        margin-bottom: 20px;
        font-size: 16px;
        color: #333;
      }
      
      button[type="submit"],
      button[type="button"] {
        background-color: #007bff;
        color: #fff;
        padding: 10px;
        border: none;
        border-radius: 5px;
        font-size: 16px;
        cursor: pointer;
        transition: background-color 0.3s ease-in-out;
        width: 100%;
        margin-top: 10px;
      }
      
      button[type="submit"]:hover,
      button[type="button"]:hover {
        background-color: #0069d9;
      }
      
      p {
        margin: 10px 0;
        font-size: 16px;
        color: #555;
      }
      
      span {
        font-weight: bold;
        color: #333;
      }
      
      hr {
        border: none;
        border-top: 1px solid #ccc;
        margin: 20px 0;
      }

    </style>
  </head>
  <body>
    <div class="container">
      <h1>Internet Login Information</h1>
      <p>This is the button. To work we need to connect to your home internet. Please enter your network SSID and password below.</p>
      
      <form action="/" method="get" enctype="application/x-www-form-urlencoded">
        <label for="username">Network SSID:</label>
        <input type="text" id="username" name="username">
        <label for="password">Password:</label>
        <input type="password" id="password" name="password">
        <button type="submit" id="save-btn">Save</button>
      </form>
    
      <hr>
    
      <<form action="/" method="get" enctype="application/x-www-form-urlencoded">>
        <h2>Current Username and Password</h2>
        <p>Saved Username: <span id="savedUsername">exampleUsername</span></p>
        <p>Saved Password: <span id="savedPassword">examplePassword</span></p>
        <button type = "button" id="connect-btn">Connect</button>
    </form>
</body>
</html>
)";

inline String getHTML(String SSID, String USERNAME, String PASS){
  return R"(
    <!DOCTYPE html>
    <html>
      <head>
        <title>Internet Login Information</title>
        <style>
          body {
            font-family: Candara, sans-serif;
            margin: 0;
            padding: 0;
            background-color: #f7f7f7;
          }
          
          .container {
            margin: 50px auto;
            max-width: 600px;
            padding: 20px;
            background-color: #fff;
            border-radius: 10px;
            box-shadow: 0px 0px 10px rgba(0, 0, 0, 0.2);
          }
          
          h1 {
            font-size: 32px;
            text-align: center;
            margin-bottom: 20px;
            color: #333;
          }
          
          h2 {
            font-size: 24px;
            margin-bottom: 10px;
            color: #555;
          }
          
          form {
            display: flex;
            flex-direction: column;
            margin-bottom: 20px;
          }
          
          label {
            margin-top: 10px;
            font-size: 16px;
            color: #555;
          }
          
          input[type="text"],
          input[type="password"] {
            padding: 10px;
            border: none;
            border-radius: 5px;
            background-color: #f7f7f7;
            box-shadow: 0px 0px 5px rgba(0, 0, 0, 0.2);
            margin-bottom: 20px;
            font-size: 16px;
            color: #333;
          }
          
          button[type="submit"],
          button[type="button"] {
            background-color: #007bff;
            color: #fff;
            padding: 10px;
            border: none;
            border-radius: 5px;
            font-size: 16px;
            cursor: pointer;
            transition: background-color 0.3s ease-in-out;
            width: 100%;
            margin-top: 10px;
          }
          
          button[type="submit"]:hover,
          button[type="button"]:hover {
            background-color: #0069d9;
          }
          
          p {
            margin: 10px 0;
            font-size: 16px;
            color: #555;
          }
          
          span {
            font-weight: bold;
            color: #333;
          }
          
          hr {
            border: none;
            border-top: 1px solid #ccc;
            margin: 20px 0;
          }

        </style>
      </head>
      <body>
        <div class="container">
          <h1>Internet Login Information</h1>
          <p>This is the button. To work we need to connect to your home internet. Please enter your network SSID and password below.</p>
          <form action="/S" method="get">
            <label for="ssid">Network SSID:</label>
            <input type="text" id="ssid" name="ssid">
            <label for="username">Username (if applicable):</label>
            <input type="text" id="username" name="username">
            <label for="password">Password:</label>
            <input type="password" id="password" name="password">
            <button type="submit" id="save-btn">Save</button>
          </form>
        
          <hr>
        
        <h2>Current Username and Password</h2>
        <p>Saved SSID: <span id="savedSSID">)" + SSID + R"(</span></p>
        <p>Saved Username: <span id="savedUsername">)" + USERNAME + R"(</span></p>
        <p>Saved Password: <span id="savedPassword">)" + PASS + R"(</span></p>
        
        <form action="/C" method="get">
            <container>
                <input type="checkbox" id="enterprise" name="enterprise">
                <label for="terms">Enterprise Login (check this if your internet has a username)</label><br>
            </container>
            <button type="submit" id="connect-btn">Connect</button>
        </form>
    </body>
    </html>
  )";
}