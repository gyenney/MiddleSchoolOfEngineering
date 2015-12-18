//  Source:  http://www.tutorialspoint.com/nodejs/nodejs_callbacks_concept.htm


// Sample Text File:  Tutorials Point is giving self learning content
//                    to teach the world in simple and easy way!!!!!

var fs = require("fs");

var data = fs.readFileSync('input.txt');

console.log(data.toString());
console.log("Program Ended");


