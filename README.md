# Algorithm-and-optimization-of-covering-problems-using-flying-drones
## Problem 
An algorithm for the optimal 3D deployment of multiple UAVs in order to cover a set of mobile targets.
Each UAV coverage performances depend on their altitude and connectivity
between each other.  We have mobile targets i.e. they can move from one position to the other.
The UAVs are equipped with cameras that can detect and follow the
mobile targets.The UAVs have the local information about the targets and
as they are connected so they can share the information between them if
any obstacle or other hazards are present in the target area.
## Definitions 
1: Coverage of an UAV
An UAV covers a target if the target position (x,y) lies in the
area covered by the radius of the UAV.
Say an UAV is at (10,10,10) and has a radius of 10 so all the targets in area
(0,0) to (20,20) will be covered by this particular UAV.

2: Connectivity of the UAVs
We say an UAV is connected to the set of UAVs if the distance between
this UAV and any of the other UAVs is less than 150. for eg. an
UAV 1 is connected to other set of UAVs n if the distance between 1 and
any of the n UAVs is less than 150.

3: Overlaping of the UAVs
We say that two UAVs overlap each other if their coverage areas coincide.

## Algorithm
(i) Positioning the targets initially
The algorithm starts by taking as inputs the initial position of all
the targets.

(ii) Initial positioning of an UAV
The first UAV is placed to the initial position of our first target

(iii) Adding more UAVs for targets uncovered
For each target we check if it is covered by the first UAV if not we
add a new UAV and then again check if there are targets that are left
uncovered. If we find any such target we add a third UAV.
Repeat the step (iii) until all the targets are covered by an UAV. 
We also maintain a spanning tree of the newly added UAVs. The UAV
of the set to which the distance of the new added UAV is less
than 150 is added as its parent node.
Each time we add an UAV we need to check step (iv) & (v).

(iv) Checking for overalping UAVs
When we add an UAV for covering a target which is uncovered by any
of the previous available UAVs. we see that the coverage area of that new
UAV should not overlap any of the available UAVs. If the new UAV overlaps we ask to reduce the
radius of that UAV until it doesn't overlap any of the available UAVs.`

v) Connectivity of UAVs
The UAVs must cover as large as area possible which can be achieved by
letting the UAVs to be widely spread but if UAVs get too much apart, the
connectivity among UAVs (at physical and link layers) will drop and the
relay network will eventually break. So we consider here that two UAVs are
connected if the distance between two is less than say 150.
When a new UAV is added we see to it that the distance between this
UAV and any of the previous UAVs in the set in the target area is less
than 150.
If the connectivity between the two UAV is lost we add a new UAV between the previous nearest UAVs  to maintian the connectivity. 
We also maintain a spanning tree of the newly added UAV which it
is connected. i.e. the UAV to which the distance of the new added
UAV  is less than 150 is added as its parent node and if the dummy
node is added then the parent of UAV.

(vI) Updating UAVs for moving targets
As the targets are mobile they can move from one position to other so we
ask if any target want to update the position. If a target moves from
we need a new area of coverage.
The new position of target may be covered by any UAV in
the set. If so its okay otherwise we need a new coverage for the new target
area, in that case we check if any of the available UAVs cover that target. 

Repeat step (iv)& (v) for the new UAV i.e. checking for non overlaping and
connectivity of the new UAV added.

(vii) Removing the unwanted UAVs
As the mobile targets move to a new location the UAV at the previous position of the target may not be
covering it.
In that case we can remove that UAV but we need to verify two conditions:

1: The UAV should not cover any of the other targets.

2: Removing the unwanted UAV does not destroy the connectivity of the
other UAVs.

If these two conditions are satisfied we remove that unwanted UAV.
We also update the spanning tree by making the parent of the node to li+1
which li was parent. Parent of li is now parent of li+1.
This is done to reduce the number of UAVs in the target area.

(viii) Optimizing the number of UAVs
This is an extension to the project.
The goal of my project was to place the UAVs in the best position to cover
all the targets and ensure connectivity between the UAVs but a step ahead
was taken in optimization by trying to move the UAVs and see if moving
them in the target area they could cover more number of UAVs. As the
UAVs cover more number of UAVs so the number of UAVs required to
cover all the targets in the target area gets reduced.
The UAVs are added to the targets position but there may be two targets
that are close enough to be covered by a single UAV and also there is a
UAV with a larger area of coverage but it is not covering the other target.
It may be that if we shift them a bit they may also cover other targets as
well which are close by. If we do not find any such UAV, we add a new UAV to the UAVs.

(ix) Checking for obstruction to target
Taking into account the local information at each UAV to avoid blocking.
We check all the targets if an obstruction lies in between the covering UAV
and the target in that case we decrease the beamwidth of the UAV by say
45degree  which increases the height of the UAV his helps to avoid
blocking..


