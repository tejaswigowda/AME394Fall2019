var http = require('http');
var hostname = process.env.HOSTNAME || 'localhost';
var port = 3000;

var callback = function(req, res){
    res.statusCode = 200;
    res.setHeader('Content-Type', 'text/plain');
    res.end('Hello World\n');
}
var server = http.createServer(callback);

server.listen(port, hostname);
