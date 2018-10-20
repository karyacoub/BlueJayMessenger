/* main.js */

// CSS: https://templated.co/embellished

const electron = require('electron');
const url = require('url');
const path = require('path');

var WebSocket = require('ws');

var serverURL = "ws://localhost:8025/chat";
const connectionTimeout = 1000;

// websocket constructor initializes object and connects to server
const client = new WebSocket(serverURL, {
    handshakeTimeout: connectionTimeout
});

const {app, BrowserWindow, Menu, ipcMain} = electron;

// set environment
process.env.NODE_ENV = 'production';

let loginWindow;
let mainWindow;

client.on('error', function(error) 
{
    app.quit();
});
 
client.on('connect', function(connection) 
{
    console.log('Connected to server');
    connection.on('error', function(error)
    {
        console.log("Connection Error: " + error.toString());
    });
    connection.on('close', function() 
    {
        console.log('Connection Closed');
    });
});

client.on('message', function(data)
{
    mainWindow.webContents.send('message-recieved', data);
});

app.on('ready', function()
{
    // Create new window
    loginWindow = new BrowserWindow({
        width: 600,
        height: 770,
        title: 'Purpl.'
    });

    // login screen doesn't need a context menu, but it is present by default, so remove it
    //loginWindow.setMenu(null);

    // Load html into window
    // url.format() formats the url as follows:
    //   file://dirname/loginWindow.html
    loginWindow.loadURL(url.format(
        {
            pathname: path.join(__dirname, 'loginWindow.html'),
            protocol: 'file:',
            slashes: true
        }
    ));

    // quit app when closed
    loginWindow.on('closed', function()
    {
        // only quit the app if user has not logged in
        if(mainWindow == null)
        {
            // close client connection to server
            client.close();
            app.quit();
        }
        else
        {
            loginWindow = null; // to aid with garbage collection
        }
    });
});

// successful logon event handler
ipcMain.on('login-button-success', function(e)
{
    // Create main window
    mainWindow = new BrowserWindow({
        width: 1000,
        height: 800,
        title: 'Purpl.'
    });

    mainWindow.loadURL(url.format(
        {
            pathname: path.join(__dirname, 'mainWindow.html'),
            protocol: 'file:',
            slashes: true
        }
    ));

    mainWindow.on('close', function() {
        client.close();
        app.quit();
    });

    // close login window
    loginWindow.close();
});

ipcMain.on('message-sent', function(e, message)
{
    try
    {
        client.send(message);
    }
    catch(e)
    {
        alert("Error - Message could not be sent.");
    }
});