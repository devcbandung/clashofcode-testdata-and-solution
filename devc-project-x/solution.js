#!/usr/bin/env node

const toIntArray = line => line.split(' ').map(i => parseInt(i));

function processData(input) {
    var lines = input.split('\n');
    var [n, k] = toIntArray(lines[0]);
    var d = toIntArray(lines[1]);
    var x = toIntArray(lines[2]);
    
    var visited = {};
    visited[1] = 1;
    for (var v of x) {
        var t = v;
        while (!visited[t]) {
            visited[t] = 1;
            t = d[t-1];
        }
    }
    console.log(Object.keys(visited).length);
} 

process.stdin.resume();
process.stdin.setEncoding("ascii");
_input = "";
process.stdin.on("data", function (input) {
    _input += input;
});

process.stdin.on("end", function () {
   processData(_input);
});
