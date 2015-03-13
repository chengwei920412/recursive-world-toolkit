

# 1. Scope #

The goal of a program written in the Recursive World Language (RWL) is to declare a virtual world, which comprises:

  * **Point landmarks:** As a sequence of 3D points, identified by its 0-based index.
  * **A topological map:** Consisting of nodes identified by its 0-based index and a set of edges among them. These define the possible paths the robot can follow during a simulation. Each node is defined by a 3D point (not pose).

An RWL program is compiled by invoking:

```
  rwt-compiler input-file.rwl
```

which generates the world and, optionally, graphically displays it to the user.

Defining the _actual_ paths to be followed during a simulation is something outside the scope of a RWL program, and is addressed by the program `wrt-dataset-simulator`.


# 2. Program structure and preprocessor #

  * **Case sensitivity:** RWL is case insensitive. That is, you can use keywords and refer to your variables and methods mix in either lower and upper case.

  * **Comments:** A comment starts with a C-style comment "//". C++ comment blocks (like /`*` ... `*`/) are not allowed.
```
   // This is a line comment which is ignored by the compiler
   <COMMAND> // A comment can also appear after a valid command line
```

  * **Lists:** The basic building block are "lists", which correspond to procedures or functions in any other procedural languages. They always have this structure (TODO: Support arguments??):
```
  LIST <NAME>
    // Here goes the contents of a LIST
  ENDLIST
```

  * **Commands:** Inside a LIST one can write one or more commands. Each command occupies exactly one line, and consists in the invocation of one primitive (see their description below), with this structure:
```
  <PRIMITIVE> [ARG1 [ARG2 ...] ]
```

  * **Minimal valid program:** Each RWL program must contain a LIST named `main`. Thus, this is the shortest possible program (which, however, does not produce any output):
```
  LIST main
  ENDLIST
```



# 3. Understanding the execution virtual machine #

The state of the execution machine has these variables:
  * **The cursor**: The current SE(3) pose. This cursor can be moved by the different primitives, and is used as the coordinate reference for primitives that provide relative coordinates.
  * **The current node ID**: The latest node ID visited. Whenever a new NODE is created, an edge is automatically created from the last node to the new one.

Notice that by means of PUSH/POP primitives the state can be saved to a stack and restored afterwards. There is no limit to the stack size apart from the machine memory.

The **initial state** of the virtual machine is:
  * SE(3) cursor set to the origin of coordinates.
  * A node is created at the origin of coordinates and set as the "active node ID".

Execution of a program:
  * Executing a RWL program consists of invoking its "main" LIST, which is the only  mandatory LIST.
  * Executing a LIST consists of interpreting its commands one by one.
  * Typically, LISTs can call to each other. Like in any other procedural language, execution is resumed at the next command after the call command.


# 4. Existing primitives #

  * **SE(3) cursor manipulation**
    * `X= <VAL>`, `Y= <VAL>`, `Z= <VAL>`: Change the cursor X,Y or Z coordinates (meters). Notice the space after the "=".
    * `YAW= <VAL>`, `PITCH= <VAL>`, `ROLL= <VAL>`: Change the cursor attitude angles (degrees). Notice the space after the "=".
    * `X+= <VAL>`, `Y+= <VAL>`, `Z+= <VAL>`, `YAW+= <VAL>`, `PITCH+= <VAL>`, `ROLL+= <VAL>`: Replace the current cursor by a pose composition of itself with another pose with the given coordinates (X,Y,Z in meters, the angles in degrees). Some examples:
      * `X+= 2` means move 2 meters forwards (not in the global +X direction).
      * `YAW+=  90` means rotate 90º anticlockwise.
      * `YAW+= -90` means rotate 90º clockwise.
    * `X-= <VAL>`,`Y-= <VAL>`,...: Is identical to `X+= -<VAL>`,`Y+=- <VAL>`,...
  * **Stack**: Saves and restores the current state of the SE(3) cursor and the current node (see section 3 above).
    * `PUSH`
    * `POP`

  * **Landmark creation**
    * `LM <RELX> <RELY> <RELZ>`: Adds a new landmark with the given relative coordinates with respect to the cursor.
    * `LM_RANDOM <X_MIN> <X_MAX> <Y_MIN> <Y_MAX> <Z_MIN> <Z_MAX>`: Adds a new landmark with a relative coordinates drawn as a random (uniform) sample over the given volume.

  * **Topological map**
    * `NODE [NO_ARC]`: Places a node at the current cursor position (orientation is ignored). Unless `NO_ARC` is specified, an edge is added from the previous node to this one. If there was already a NODE at the insertion point (or within 0.1 meters) it is assumed that the intention was to loop closure and the edge is created to the existing node. After all, the current node ID in the execution state machine is set to this last node.
    * `NODE <RELX> <RELY> <RELZ> [NO_ARC]`: Exactly like `NODE` but creates the node at the given relative coordinates with respect to the cursor.


  * **Flow control**
    * `CALL [*N] <LIST_NAME>`: Calls another LIST (just like invoking a subroutine in any procedural language). The optional `*N` part indicates repeating the call `N` times.


  * **Miscellaneous**
    * `RANDOMIZE`: Initializes the random number generator from the system clock.
    * `RANDOMIZE <SEED>`: Initializes the random number generator with a predefined seed.