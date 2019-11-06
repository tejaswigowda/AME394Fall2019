var express = require("express");
var app = express();
var MS = require('mongoskin');
var bodyParser = require('body-parser');
var errorHandler = require('errorhandler');
var methodOverride = require('method-override');
var hostname = process.env.HOSTNAME || 'localhost';
var port = 3000;
var VALUE1 = "";
var VALUE2 = "";


var db = MS.db("mongodb://34.216.181.26:27017/sensorData"); //change this!!!

app.get("/", function (req, res) {
  res.send("Temperature: " + (VALUE1*1.8 + 32) + "F \r Humidity: " + VALUE2 + "%");
});

app.get("/getValue", function (req, res) {
  var ts = parseInt(req.query.ts);
	db.collection("data").findOne({ts:{$lte:ts}, ts:{$gt:0}}, function(err, result){
    res.send(JSON.stringify(result));
  });
});


app.get("/getAverage", function (req, res) { // edit this for A6
  var ts = parseInt(req.query.ts);
  var begin = ts;
  var end = ts;
	db.collection("data").find({ts:{$lte:ts}, ts:{$gt:0}}).toArray(function(err, result){
    var ret = { // calulate from result
     t: 0,
     h: 0
    }
    res.send(JSON.stringify(ret));
  });
});


app.get("/setValue", function (req, res) {
  var v1 = decodeURIComponent(req.query.t);
  var v2 = decodeURIComponent(req.query.h);
  VALUE1 = v1;
  VALUE2 = v2;
	var newObj = {
		t: v1,
		h: v2,
		ts: new Date().getTime()
	}

	db.collection("data").insert(newObj, function(err, result){});

  res.send(VALUE1 + "\n" + VALUE2);
});

app.use(methodOverride());
app.use(bodyParser());
app.use(express.static(__dirname + '/public'));
app.use(errorHandler());

console.log("Simple static server listening at http://" + hostname + ":" + port);
app.listen(port);
