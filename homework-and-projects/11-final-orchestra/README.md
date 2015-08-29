Orchestra (Final Project)
=========================

### Gideon Leeper, Kyle Oleksiuk, Aida Piccato, Mary Taft ###

**Setup**
<ul>
<li>install SDL and SDL Mixer on whichever computer will run the server (note: program can be tested on a single computer)</li>
<li> Linux: sudo apt-get install libsdl2-dev; sudo apt-get install libsdl2-mixer-dev </li>
<li> MacOS: not sure </li>
<li> cd to code/sounds/ and extract the .ogg files from the linked .zip file (didn't put it in GitHub because it's a relatively big file) </li>
<li> if testing on one machine: </li>
<li>type "make" in the code/ folder</li>
<li>open up a couple terminals</li>
<li>run ./server in one and ./client in the other(s)
<li> if testing on multiple machines: </li>
<li>open client.c with a text editor (oh joy), find and replace 127.0.0.1 with the IP address of whichever computer is running the server</li>
<li>follow the above steps for a single machine</li>
</ul>

**Structure**
<ul>
<li>networking, forking for multiple clients, good stuff</li>
<li>Each client represents an instrument</li>
<li>STRUCTS talk about structs that's important</li>
<li>client sends struct information to the server</li>
<li>server plays appropriate sounds</li>
</ul>

**Usage**
<ul>
<li>choose an instrument at the prompt (note: if it doesn't immediately register, hit Enter/Return and it should go)</li>
<li>hit any of the following keys, which are mapped like a piano keyboard, to play the notes of a chromatic scale:</li>
 W E   T Y U
A S D F G H J K
<li>toggle between instruments at any point by hitting any bottom-row letterkey except Z (that is, X C V B N M)</li>
<li>hit Z in the client to exit</li>
</ul>

**Features**
<ul>
<li>Six different playable instruments (piano, flute, cello, trumpet, clarinet, violin)</li>
<li>Toggling of instruments by clients while playing using the XCVBNM keys</li>
<li>Server capable of playing several sounds at once, allowing for multiple clients to make music together</li>
<li>Two octaves represented on each instrument, the second of which is accessed by holdinging the SHIFT key</li>
<li>Holding down keys allows for the continuous playing of sounds</li>
</ul>

**Potential Improvements**
<ul>
<li>shorten sound file duration so that a quick key press doesn't render a long note</li>
<li>etc., there are plenty</li>
</ul>
