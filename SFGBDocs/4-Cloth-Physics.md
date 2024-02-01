# **Cloth Physics**

## **Preparations**
1. To compose cloth physics, you need first install **Physics Editor Interface**. This is an additional blender addon that can be downloaded here.
2. "Starfield Havok Physics Editor" addon adds new **Physics Node Tree** and **useful functionalities** for custom havok physics data composition.
3. Make sure your main addon "Starfield Geometry Bridge" and "Starfield Havok Physics Editor" have the **same version number**. You can check version number from blender's addon panel (See Image 1).
![Image 1](/cloth/image1.png)
4. Once successfully installed, you should find an additional panel in "Tool" sidebar. (See Image 2)
![Image 2](/cloth/image2.png)

## **Prerequisite Knowledge**
1. **What is Cloth Simulation**: Cloth simulation in general is to use the behaviour of discretised "particles" with physics properties to simulate the behaviour of a piece of cloth or skin.
2. **Key Components in Cloth Sim**: 
    
    a) ***Particles***: In cloth simulation, particles are used to represent and simulate the behaviour of individual points or vertices in a cloth mesh. Instead of simulating the entire cloth as a continuous surface, cloth simulation often breaks it down into a system of particles connected by springs or constraints. These particles interact with each other and their environment to create realistic cloth movement and deformation.
    
    b) ***Constraints***: Constraints are limitations or rules applied to the movement or behaviour of particles within the simulation. They are often used to control the interactions between particles representing different points on the cloth.
    
    c) ***Colliders***: Colliders are physics entities that particles or other colliders can collide with.

## **Edit Physics in Node Editor**
1. Check "[**Important Notes**](#Important%20Notes)" below before making your first composition. 
2. Check "[**Graph and Nodes**](#Graph%20and%20Nodes)" to better understand the graph and how data flows.
3. Open physics editor interface: Switching to "HCL Physics Editor" in any UI Area by **changing the "Editor Type" at left-top conner to "HCL Physics Editor"** (See Image 3).
![Image 3](/cloth/image3.png)
4. Click on "new" button at top of the window to **create a new node tree** and set the name to your likings.
5. Once done, you should be able to add new nodes into the node tree (See Image 4). **Start by Adding an "Graph Output" node**. Press "**Shift + A**" and locate "**Output -> Graph Output**".
![Image 4](/cloth/image4.png)
6. **You can't export your composition when there's an error present**. The error message shows that the output node doesn't receive any valid input (See Image 5). 
![Image 5](/cloth/image5.png)
7. "**Shift + A -> Physics Data -> Two State Physics Data**" to add a physics data node. Connect the physics data node to output node.
8. Eliminate the errors by providing valid inputs and **check the [Demo Project](https://www.nexusmods.com/starfield/mods/8262?tab=files) for what's missing in your composition**. You may end up having a Node Tree like in the [Demo Project](https://www.nexusmods.com/starfield/mods/8262?tab=files) (See Image 6).
![Image 6](/cloth/image6.png)

### ***Important Notes***
1. The graph takes two things as input: A **skeleton with cloth bones** and a **simulation mesh** for cloth particles and constraints. Use "Shift + A -> Input -> Armature Input & Mesh Input" to tell the node tree which skeleton and mesh object to use.
2. Simulation mesh should **be weighted to the skeleton**! If you don't sure how to weight your simulation mesh, you can open any clothes nif with physics data with "**Visualize Havok Sim Cloth Data**" on and see how Beth did their job (**hclSimClothData_XXX **is the simulation mesh used by Beth).
3. For greater stability, it's recommended to use "**Stretch Link**" in the constraints together with "**Standard Link**" constraint.
4. When adding nodes, **hovering on a node in the node menu** before adding it will show its description. Be sure not to miss that since it tells you what the node does.
5. There is a button inside right-click menu to Mark Selected Elements in Edit mode. You can then get the indices of your selected elements using a combination of "**Mesh Input** -> **Mesh Attribute Selection**"  nodes.

## **Graph and Nodes**
The included Diagram (Image 7) and node graph Example (Image 8) visualizes the [Below Description](#graph-for-cloth-physics)
![Image 7](/cloth/image7.png)
![Image 8](/cloth/image8.png)

### ***Graph for Cloth Physics***
1. From low level to high level, from left to right, a graph takes "Simulation Mesh" and "Skeleton" as input and go through 3 stages to produce physics data.
2. **Stage 1** is how particles are produced from input mesh,  which is what "**Particles From Mesh**" node does.
3. **Stage 2** is how particles are constrained together. Use the nodes in "**Constraint**" category and finally link to "**Sim Cloth Data**" node to proceed.
4. **Stage 3** is the time to define whether you want collisions to happen between certain particles and colliders (optional) and how physics bones are driven by simulation (required). Optionally you can use "**Simulation -> Disable Collision**" node to achieve that, and finally link the output to "**Two State Physics Data**" node. At this stage, also use "**Physics Bone -> Simple Triangle Bone Driver**" node and provide it with a list of bones (use "**Match Bone Name**" node in "**Select**" category) to produce "**Physics Bones**" data and feed it to "**Two State Physics Data**" node.

## **Nodes for Cloth Physics**
### ***Nodes for Cloth Physics: Input***
1. **Armature Input**: Allow setting an armature object for other nodes to reference. All Armature Input nodes share the same skeleton object.
    a) *__Inputs__*:   
    	None
   
    b) *__Outputs__*: 
    	hkaSkeleton: The skeleton for other node to reference. (For example, select a bone from it)

2. **Mesh Input**: Allow setting an mesh object for other nodes to reference. All Mesh Input nodes share the same mesh object.
    a) *__Inputs__*: 
    	None
    
    b) *__Outputs__*: 
    	Simulation Mesh: The mesh object for other node to reference. (For example, select vertices or edges from it)

### ***Nodes for Cloth Physics: Output***
1. **Graph Output**: Output node of physics data. 
    a) *__Inputs__*: 
    	Physics Data: The Physics Data for output. Physics Data comes from nodes in *Category: Physics Data*.
    
    b) *__Outputs__*: 
    	None

2. **Viewer Output**: Output node for visualization.
    
    a) *__Inputs__*: 
    	Any: Allow any type of input. Used for visualization.
    
    b) *__Outputs__*: 
    	None

### ***Nodes for Cloth Physics: Select***
1. **Mesh Attributes Selection**: Outputs a set of indices based on whether the attribute value of each element satisfies the selection condition.
    a) *__Inputs__*: 
    	Mesh: The mesh object to select elements from.
    
    b) *__Outputs__*: 
    	Indices On Domain: A set of selected indices on a certain Domain ("POINT", "EDGE" or "FACE").
    
    c) *__Parameters__*:
    	Domain: Either "Point" or "Edge" or "Face", the type of element being selected.
    	Type: Attribute type. The type of attribute value.
    	Attribute: Attribute name.
    	Operator: Methods to compare attribute value with Operand parameter.
    	Operand: Threshold value, used together with Operator parameter.

2. **Pick Bone From Skeleton**: Outputs a bone that is selected from input skeleton
    a) *__Inputs__*: 
    	Skeleton: The skeleton to choose bone from.
    
    b) *__Outputs__*: 
    	Bone: The selected bone.
    
    c) *__Parameters__*: 
    	Bone: The selected bone name.

3. **Match Bone Names**: Outputs a set of bones by name matching from input skeleton
    a) *__Inputs__*: 
    	Skeleton: The skeleton to choose bones from.
    
    b) *__Outputs__*: 
    	Bones: The selected set of bones.
    
    c) *__Parameters__*: 
    	Match Mode: Method to match string with bone names.
    	Matching String: The object string for matching
    	Matched Bone Dropdown: For display. Shows which bones are selected by this node.

4. **Combine Bone Selection**: Outputs a set of bones by combining input sets of bones
    a) *__Inputs__*: 
    	Bone(s) A: A bone or a set of bones.
    	Bone(s) B: The second bone or set of bones.
    
    b) *__Outputs__*: 
    	Bones: The combined set of bones.

### ***Nodes for Cloth Physics: Simulation***
1. **Sim Cloth Data**: Combine input Particles and Colliders to form Simulation Cloth Data. 
    a) *__Inputs__*: 
    	Particles: Constrained Particles defined in previous stage. (See [Pre-requisite Knowledge](#Prerequisite%20Knowledge): "**a. Particles**" & "**b. Constraints**").
           Colliders: Colliders for simulation. Maximum 32 nodes from *Category: Colliders*.
    
    b) *__Outputs__*: 
    	Cloth Data: Output Simulation Cloth Data. 
    
    c) *__Parameters__*:
    	Gravity Vector: Gravity's direction and value. (0, 0, -9.81) is earth gravity that pointing downwards.
    	Global Damping Per Second: Simulates air viscosity or resistance. How much percentage of velocity of a particle will lose every second.

2. **Particles From Mesh**: Generate Particles at each vertex of the input mesh. (Particles are key elements in **Stage 2**)
    
    a) *__Inputs__*: 
    	Mesh: The mesh to generate particles from.
    	Bind To Bone: Which bone the fixed particles will copy movements from.
    	Fixed Particle Indices: Which particles are fixed (connects to non-cloth sim areas). 
    
    b) *__Outputs__*: 
    	Particles: A group of unconstrained cloth Particles.
    	
    c) *__Parameters__*:
    	Particle Mass: The mass of each particle.
    	Particle Radius: How large each particle is.
    	Particle Friction: The friction factor of each particles.

3. **Links From Mesh**: Generate Links from selected edges of the input mesh. (used to define constraints in *Category: Constraints*)
    a) *__Inputs__*: 
    	Mesh: The mesh to select links from.
    	Edge Indices: Selected edge indices on Domain "Edge". (Default: all edges)
   
    b) *__Outputs__*: 
    	Links: A selected set of edges with stiffness value.
    
    c) *__Parameters__*:
    	Link Stiffness: How strong the links are. (1 means infinitely strong and 0 means infinitely weak)

4. **Disable Collision**: Disables collision between a Collider and selected Particles.
    a) *__Inputs__*: 
    	Cloth Data: Input Simulation Cloth Data to operate on.
    	Particle Indices: Selected set of vertex indices on Domain "Point".
    
    b) *__Outputs__*: 
    	Cloth Data: Output Simulation Cloth Data after the operation. 
    
    c) *__Parameters__*:
    	Collider: Collision between this Collider and selected particles is disabled.

5. **Set Particle Attributes**: Set Mass, Radius and Friction for selected Particles from input set of Particles.
    a) *__Inputs__*: 
    	Particles: Input set of Particles to operate on.
    	Particle Indices: Selected set of vertex indices on Domain "Point".
    
    b) *__Outputs__*: 
    	Particles: Output set of Particles with updated physics properties. 
    
    c) *__Parameters__*:
    	Particle Mass: The mass of each particle.
    	Particle Radius: How large each particle is.
	    Particle Friction: The friction factor of each particles.

### ***Nodes for Cloth Physics: Constraints***
1. **Standard Link**: Default cloth simulation links between particles. Constraint on the length of the links to their default length.
    a) *__Inputs__*: 
    	Particles: Input set of Particles to add constraint to.
    	Links: A set of links to connect Particles. (Links are from "**Links From Mesh**" node)
    
    b) *__Outputs__*: 
    	Particles: Output set of Particles with this Constraint.
    
    c) *__Parameters__*:
    	Show Constraint: Show Vis Mesh of this constraint.

2. **Stretch Link**: Constraint the stretchiness of links between particles. Useful for cloth with elastic properties.
    a) *__Inputs__*:
    	Particles: Input set of Particles to add constraint to.
    	Links: A set of links to connect Particles. (Links are from "**Links From Mesh**" node)
    
    b) *__Outputs__*: 
    	Particles: Output set of Particles with this Constraint.
    
    c) *__Parameters__*:
    	Show Constraint: Show Vis Mesh of this constraint.

3. **Global Bone Plane Constraint**: Constraint Particles to a Plane that copies the rotation of the input bone.
    a) *__Inputs__*: 
    	Particles: Input set of Particles to add constraint to.
    	Bone: Which Bone Axes the constraint plane is in and rotates with.
    	Particle Indices: Which Particles are constrained. The input is a selected set of vertex indices on Domain "Point".
    
    b) *__Outputs__*: 
    	Particles: Output set of Particles with this Constraint.
    
    c) *__Parameters__*:
    	Show Constraint: Show Vis Mesh of this constraint.
    	Plane Normal Direction: Normal direction of the constraint plane.
    	Stiffness: The strength of this constraint.

4. **Local Range Constraint**: Constraint Particles within a range of their initial positions
    a) *__Inputs__*: 
    	Particles: Input set of Particles to add constraint to.
    	Particle Indices: Which Particles are constrained. The input is a selected set of vertex indices on Domain "Point". Default: all particles.
        
    b) *__Outputs__*: 
    	Particles: Output set of Particles with this Constraint.
        
    c) *__Parameters__*:
    	Show Constraint: Show Vis Mesh of this constraint.
    	Particle Stiffness/Base Stiffness: The strength of this constraint. (0 means not at all, 1 means infinitely strong)
    	Minimum Range: Particles within this range will move freely, but outside this range will receive a corrective force.
    	Mode "Fixed": All particles get the same constraint power no matter how far they are from the body.
    	Mode "Cascade": Particles that are close to the end of a cloth bone chain are less constrained than those are far.
    	Mode "Cascade" -> Cascade Falloff Factor: How fast the constraint power decreases as the particle gets closer to the end of the cloth bone chain. (the smaller the value, the faster the constraint power decreases)
    	Constraint Normals: Weather to take normal directions of particles into consideration.

### ***Nodes for Cloth Physics: Colliders***
1. **Capsule Collider**: A collider that has a capsule shape.
    a) *__Inputs__*: 
    	Bind To Bone: The bone this collider copies movements from. (weighted to this bone)
    
    b) *__Outputs__*: 
    	Collider: The collider. Which can then be fed into "**Sim Cloth Data**" node.
    
    c) *__Parameters__*:
    	Start Position: Location of the starting end in Bone Axes.
    	End Position: Location of the ending end in Bone Axes.
    	Radius: The radius of the capsule shape.

2. **Tapered Capsule Collider**: A capsule Collider whose one end can be bigger or smaller than the other end.
    a) *__Inputs__*: 
        Bind To Bone: The bone this collider copies movements from. (weighted to this bone)
    
    b) *__Outputs__*: 
        Collider: The collider. Which can then be fed into "**Sim Cloth Data**" node.
    
    c) *__Parameters__*:
        Start Position: Location of the starting end in Bone Axes.
        End Position: Location of the ending end in Bone Axes.
        Start Radius: The radius of the capsule shape at the starting position.
        End Radius: The radius of the capsule shape at the ending position.

### ***Nodes for Cloth Physics: Physics Data***
1. **Two State Physics Data**: Combine Simulation Cloth Data, Simulation Mesh and Physics Bones (from *Category: Physics Bones*) to make Physics Data for graph output.
    a) *__Inputs__*: 
		Cloth Data: The Simulation Cloth Data after **Stage 3**.
        Simulation Mesh: The mesh object used throughout the graph.
        Physics Bones: A set of Physics Bones defined by Driver nodes in *Category: Physics Bones*.
        
    b) *__Outputs__*: 
        Physics Data: The composed Physics Data for output.

### ***Nodes for Cloth Physics: Physics Bones***
1. **Simple Triangle Bone Driver**: Drive Cloth Bones with the closest triangle from simulation to create physics visual effects. __Physics Bones are Cloth Bones **driven** by simulation.__
    a) *__Inputs__*: 
        Bones: Input Cloth Bones to be driven.
        Simulation Mesh: Underlying mesh.
    
    b) *__Outputs__*: 
        Physics Bone: Output Physics Bones. Physics Bones are Cloth Bones **driven** by simulation.
    
    c) *__Parameters__*
        Mode: The method to pick closest triangle from a cloth bone. Both methods work similarly.