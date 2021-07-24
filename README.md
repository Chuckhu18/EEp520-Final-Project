# EEp520-Final-Project

Final project of Software Engineering For Embedded Applications

Game intoduction
---
This is a Maze and Tank combined game. use `a`,`s`,`d`,`w` for movement, and `space` for shooting blue enemy.
The goal of the game is to kill enemys and find a way out.
You will respawn if you hit by enemys.
![alt text](https://github.com/ChuckHu18/EEp520-Final-Project/blob/master/Tank_Maze.png?raw=true)


Get started to run the program
---
Using docker container to mount on local drive.
To start a Docker container with ENVIRO pre-loaded into it, do:

```bash
docker run -p80:80 -p8765:8765 -v $PWD:/source -it klavins/enviro:v1.61 bash
esm start
```

The above commands do the following:

- The `-p80:80 option maps *port* 80 from the Docker container to ports on your host computer. This should allow you to go to 
    > [http://localhost](http://localhost)
    with your web browser and see the ENVIRO client. It should say "Error: Failed to fetch. Is the server running?" at this point. 

- The `-p8765:8765` option allows the ENVIRO client to communicate with the `enviro` server (not yet running) via a *WebSocket*.

- The command `esm start` uses the <u>e</u>nviro <u>s</u>etup <u>m</u>anager to start a web server from which your browser can access the ENVRIO client.


Make the project and start the enviro sever as follows.
```bash
make
enviro
```

Then navigate to [http://localhost](http://localhost) you should see a maze and your tank poped up. 

You can press `Ctrl-C` to stop the enviro server. 

Acknowledges
---
This project was built based on [enviro](https://github.com/klavinslab/enviro#dockerhub-images) system by Professor Eric Klavins.

Methods used:
- Manipulation of multiple agents and sensors
- Collision handlers
- Keyboard events for movement
- Teleporting when collision with objects
- Agent creation and removal by using collision handlers
- Simple algorithm for for wandering object
