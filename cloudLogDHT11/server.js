var express = require("express");
var app = express();
var bodyParser = require('body-parser');
var errorHandler = require('errorhandler');
var methodOverride = require('method-override');
var hostname = process.env.HOSTNAME || 'localhost';
var port = 3000;
var VALUE1 = "";
var VALUE2 = "";

app.get("/", function (req, res) {
    res.redirect("/index.html");
});

app.get("/getValue", function (req, res) {
  res.send(VALUE1 + "\r" + VALUE2);
 // res.send(VALUE1);
 // res.send(VALUE2);
});

app.get("/setValue", function (req, res) {
  var v1 = decodeURIComponent(req.query.v1);
  var v2 = decodeURIComponent(req.query.v2);
  VALUE1 = v1;
  VALUE2 = v2;
  res.send(VALUE1 + "\n" + VALUE2);
});

app.use(methodOverride());
app.use(bodyParser());
app.use(express.static(__dirname + '/public'));
app.use(errorHandler());

console.log("Simple static server listening at http://" + hostname + ":" + port);
app.listen(port);
