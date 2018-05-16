/* main.js */

// CSS: https://templated.co/embellished

const electron = require('electron');
const url = require('url');
const path = require('path');

var WebSocket = require('ws');
var serverURL = "ws://localhost:8025/chat";
var client = new WebSocket(serverURL);

const {app, BrowserWindow, Menu, ipcMain} = electron;

// set environment
process.env.NODE_ENV = 'production';

let loginWindow;
let mainWindow;

client.on('connectFailed', function(error) 
{
    alert('Connect Error: ' + error.toString());
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
        // close client connection to server
        client.close();

        // only quit the app if user has not logged in
        if(mainWindow == null)
        {
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
    console.log(window.location.host);
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

    mainWindow.on('close', function(){
        app.quit();
    });

    // close login window
    loginWindow.close();
});