# Webpage for CS 241

###How to build
Use the following commands in your vagrant development environment to get this up and running
```bash
npm install
bower install
grunt compass:dev
grunt compass:foundation
grunt uglify
grunt
```
If something goes wrong try
```bash
npm install -g grunt-cli
```

###How to deploy
run the publish script
```bash
./publish
```
