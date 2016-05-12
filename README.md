*Overview: This is a 3D representation of a ladybug. There are basically two types of commands in my program:
- Model view/projection matrix change command
- Movement command.

*Instructions:
1. To change model view/projection matrix, there are 3 options, all of which require holding CTRL:
	a. Change eyepoint to left/right (model view): drag the mouse left/right while clicking the left button
	b. Change zoom (model view): drag the mouse up/down while clicking the middle button
	c. Change top edge of the frustum (projection): drag the mouse up/down while clicking the right button

2. To make the insect move: hold UP/DOWN key. As it moves, you can see its upper joint is rotating around 2 orthogonal directions x and z.
This implementation is for both part B and part G1 of the assignment.

3. ADDITIONAL FEATURES: Beside walking by holding UP/DOWN key, user can also specify a goal for the insect to walk to by applying the following steps: 
	- Activate/Deactivate this mode by pressing the 'm' button
	- Click anywhere on the screen for the insect to walk to
Note: this mode only works properly when the insect starts from the origin, i.e. middle of the screen. Therefore, please deactivate and then activate it 
again for another try.