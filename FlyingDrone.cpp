#include <iostream>
#include <vector>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
using namespace std;
int t = 0,ua=0;
struct area {
    int min_x ;
    int min_y ;
    int max_x ;
    int max_y ;
};
area ar;
struct targets {
    int id;
    int position[2];
    int coveruav;
};
struct uavs {
    int id;
    double pos[3];
    int radius;
    int beamlength;
    double altitude;
    int obs[2];
    int parent;
};
vector<uavs> uav;
vector<targets> target;
void checkconnectivity(vector<uavs>& uav, int);
void updatetarget(int);
/*Method to add a UAV in the list of UAVs with its details like- coverage radius, 
beamlength, obstruction to the target as the UAVs has information already of the obstructions of the area.*/

void adduav()
{    
    int r, b, x, y, n = ua + 1;; char ch;
    uav.resize(n);
    //Push back new subject created with default constructor.
    uav.push_back(uavs());
    cout << "ENTER THE COVERAGE RADIUS OF THE UAV "<<n<<endl;
    cin >> r;
    cout << "ENTER THE BEAMLENGTH OF THE UAV " << n<<endl;
    cin >> b;
    cout << "ANY LOCAL OBSTRUCTION TO ?? " << n<<endl;
    cin >> ch;
    if (ch == 'y' || ch == 'Y')
    {
        cout << " ENTER THE LOCATION OF THE OBSTRUCTION x-axis FOLLOWED BY THE y-axis" << endl;
        cin >> x; cin >> y;
        uav[n].obs[0] = x;
        uav[n].obs[1] = y;

    }
    uav[n].id = n;
    uav[n].parent = 0;
    uav[n].radius = r;
    uav[n].beamlength = b;
    uav[n].altitude = r / tan(b);
    uav[n].pos[2]= uav[n].altitude;
    ua += 1;
}
/*Method to get the coverage area of the targets combined. */
void areas()
{
    ar.min_x=target[1].position[0];
    ar.min_y = target[1].position[1];
    ar. max_x= target[1].position[0];
    ar.max_y = target[1].position[1];
    for (int i = 2; i <= t; i++)
    {
        if (target[i].position[0] < ar.min_x && target[i].position[1] < ar.min_y)
        {
            ar.min_x = target[i].position[0];
            ar.min_y = target[i].position[1];
        }
        else if (target[i].position[0] > ar.max_x && target[i].position[1] > ar.max_y)
        {
            ar.max_x = target[i].position[0];
            ar.max_y = target[i].position[1];
        }
    }
    cout << "THE AREA OF COVERAGE IS (" << ar.min_x<< " , "<<ar.min_y<<" ) "<<" TO ("<<ar.max_x<<" , "<<ar.max_y<<" ) "<<endl;
}
/*Method to add a target */
void addtarget(int t)
{
    int r[2];
    target.resize(t);
    target.push_back(targets());
    cout << "ENTER THE COORDIANTE POSITION OF THE TARGET x-axis FOLLOWED BY THE y-axis " << endl;
    cin >> r[0]>>r[1];
    target[t].id =t;
    target[t].position[0]= r[0];
    target[t].position[1] = r[1];
    //target[t].time = tt;
    cout << "TARGET " << target[t].id << " has position (" << target[t].position[0]<<","<<target[t].position[1] << ") "<< endl;
    if (t > 2)
    {
        areas();
    }
}

/*Method to check if there is an obstruction in between the UAV and teh tagert. In case we find some 
We chaneg the beamlength of the UAV by 45degree. */
void checkobstruction(int i, int j)
{
    double d1, d2, d3;
    d1 = sqrt(pow((uav[i].obs[0] - target[j].position[0]), 2) + pow((uav[i].obs[1] - target[j].position[1]), 2));
    d2 = sqrt(pow((uav[i].pos[0] - uav[i].obs[0]), 2) + pow((uav[i].pos[1] - uav[i].obs[1]), 2));
    d3 = sqrt(pow((uav[i].pos[0] - target[j].position[0]), 2) + pow((uav[i].pos[1] - target[j].position[1]), 2));
    if ((d1 + d2) == d3)
    {
        cout << " THERE IS A OBSTRUCTION TO THE TARGET MOVING THE BEAMLENGTH BY 45 DEGREE"<<endl;
        uav[i].beamlength -= 45;
        uav[i].pos[2] = uav[i].radius / tan(uav[i].beamlength);
        cout << "THE NEW LOCATION OF THE UAV " << i << " IS (" << uav[i].pos[0] << "," << uav[i].pos[1] << "," << uav[i].pos[2] << ")" << endl;
    }
}

/*Method to check if the coverage area of an UAV overlapps with any other UAV in case of one we ask to 
the radius of that particular UAV untill it is no longer Overlapping*/
void cond(int i)
{
    double X = uav[ua].pos[0] - uav[i].pos[0];
    double Y = uav[ua].pos[1] - uav[i].pos[1];
    double D = sqrt((X*X + Y*Y));   // distance between two centers
    double sumRad = uav[ua].radius + uav[i].radius;
    // Testing for overlap
    if (!(D < sumRad))
    {
        if (i != ua)
            cout << " non overlapping uav " << i << " to " << ua << endl;
    }
    else
    {
        if (i != ua)
        {
            int p;
            cout << " overlapping uav " << i << " to " << ua << " please change the radius of the uav" << endl;
            cin >> p;
            uav[ua].radius = p;
            cout << " the new radius is" << uav[ua].radius << endl;
            cond(i);
        }
    }
}
//Checking on overlapping for all teh UAVs
void checkoverlap()
{
    for (int i = 1; i <= ua; i++)
        cond(i);
}

/*Method to add a check if the present UAVs is enough to cover the targets otherwise 
we add a new UAV and check that the new UAV is not overlapping as well as maintains 
connectivity with the other UAVs*/
void checkcover()
{
    int f = 0, x, y, c = 0;
    for (int i = 1; i <= t; i++)
    {
        f = 0; c = 0;
        for (int j = 1; j <= ua; j++)
        {
            if (!(((((target[i].position[0]) <= (uav[j].pos[0] + uav[j].radius)) && ((target[i].position[0]) >= (uav[j].pos[0]))) || (((target[i].position[0]) >= (uav[j].pos[0] - uav[j].radius)) && ((target[i].position[0]) <= (uav[j].pos[0])))) && ((((target[i].position[1]) <= (uav[j].pos[1] + uav[j].radius)) && (target[i].position[1]) >= (uav[j].pos[1])) || (((target[i].position[1]) >= (uav[j].pos[1] - uav[j].radius)) && (target[i].position[1]) <= (uav[j].pos[1])))))
            {
                f++;
                if (f == (ua))
                    c = 1;
            }
            else
            {
                
                cout << "the target (" << target[i].position[0] << "," << target[i].position[1] << ") is covered by the uav" <<j<<" at ("<< uav[j].pos[0] << "," << uav[j].pos[1] << " ," << uav[j].pos[2] << ")" << "WHOSE RADIUS IS " << uav[j].radius << endl;
                target[i].coveruav = j;
                break;
            }
        }
        if (c == 1)
        {

            x = target[i].position[0]; y = target[i].position[1];
            cout << "ADDING  NEW UAV TO (" << x << "  , " << y << " )" << endl;
            adduav();
            uav[ua].pos[0] = x;
            uav[ua].pos[1] = y;
            uav[ua].pos[2] = uav[ua].altitude;
            target[i].coveruav = ua;
            cout << " UAV " << ua << " ADDED TO (" << uav[ua].pos[0] << " ," << uav[ua].pos[1] << " ," << uav[ua].pos[2] << " )" << " WITH COVERAGE RADIUS OF " << uav[ua].radius << endl;
            checkoverlap();
            checkconnectivity(uav,ua);
            
        }
    }
}

/*Method to check the connectivity between the UAVs. 
Two UAVs are connected if the distance between a UAV and any of the rest of the UAV is <150. 
If we find any we add a UAV between that UAV and the nearest UAV. */
void checkconnectivity(vector<uavs>& uav, int u)
{
    double s, mindist =10000;int p = 0, t = 0;
    for (int i = 1; i < u; i++)
    {
        s = sqrt(pow((uav[u].pos[0] - uav[i].pos[0]), 2) + pow(((uav[u].pos[1]) - (uav[i].pos[1])), 2) + pow(((uav[u].pos[2]) - (uav[i].pos[2])), 2));
        cout << "THE DISTANCE OF  "<<u<<" TO "<<i<<" IS " << s<<endl;
        if (s < mindist )
        {
            mindist = s;
            p = i;
        }
    }
    cout << "THE MININMUM DISTANCE IS " << mindist << endl;
    if (mindist < 150 && mindist>0)
    {
        uav[u].parent = uav[p].id;
        cout << " parent of " << u << " is " << uav[p].id << endl;
        cout << "UAV " << u << " HAS BEEN ADDED TO UAV " << p << " WITH DISTANCE BETWEEN THEM " << mindist<<endl;
    }
    else 
    {
        cout << "THERE ARE NO UAVS WITH DISTANCE LESS THAN 150 ADDING AN UAV TO MAINTAIN CONNECTIVITY" << endl;
        adduav();
        uav[u+1].pos[0] = (uav[u].pos[0] + uav[p].pos[0]) / 2;
        uav[u+1].pos[1] = (uav[u].pos[1] + uav[p].pos[1]) / 2;
        uav[u+1].pos[2] = (uav[u].pos[2] + uav[p].pos[2]) / 2;
        u++;
        cout << " uav " << u << " added to the position " << uav[u].pos[0] << endl;
        checkconnectivity(uav, u);
        uav[u - 1].parent = u;
        cout << "THE PARENT OF " << u - 1 << " IS " << u << endl;
    }
    ua = u;
}

//First UAV is added to teh first target position 
void placeuav()
{
    adduav();
    uav[1].pos[0] = target[1].position[0];
    uav[1].pos[1] = target[1].position[1];
    target[1].coveruav = 1;
    cout << " UAV " << ua << " ADDED TO (" << uav[ua].pos[0] << " ," << uav[ua].pos[1] << " ," << uav[ua].pos[2] << " )" << " WITH COVERAGE RADIUS OF " << uav[ua].radius << endl;
}

//Method to keep track of targets covered by the UAVs
vector<int> coveringuav(int x)
{
    vector<int> c; int b = 0;
    for (int j = 1; j <= t; j++)
        {
            if (target[j].coveruav == x)
            {
                b++; 
                c.push_back(j); cout << " uav " <<x << " is covering target  " << j << endl;
            }
        }    
    c.resize(b);
    return c;
}

//Method to check connectivity between UAVs
int checkconn(vector<uavs>& uav, int u,int t)
{
    int f = 0;
    for (int i = 1; i <= t; i++)
    {
        if (uav[i].parent == u)
            f = i;
    }
    int x = uav[u].parent;
    double s = sqrt(pow((uav[f].pos[0] - uav[x].pos[0]), 2) + pow(((uav[f].pos[1]) - (uav[x].pos[1])), 2) + pow(((uav[f ].pos[2]) - (uav[x].pos[2])), 2));
    cout << "distance between " << x << "at pos" <<uav[x].pos[0]<< " and " << f <<" at pos" << uav[f].pos[0] << " is " << s << endl;
    if (s > 150)
    {
        if (coveringuav(x).size() == 0 || coveringuav(f).size() == 0)
        {
            cout << " as the uav is no longer reuired it can be deleted " << endl;
            return 1;
        }
        else
            return 0;
    }
        
    else
        return 1;
}

/*Method to remove unncessary UAVs as when a target is moved the UAV at that position may not be 
covering any other target and could be removed*/
void rmuav()
{
    cout << " CHECKING FOR UNNECESARRY UAVs" << endl;
    int f = 0;
    for (int i = 1; i <= ua; i++)
    {
        f = 0;
        for (int j = 1; j <= t; j++)
        {
            if (target[j].coveruav != i)
                f++;
        }
        if (f == t)
        {
            cout << " UAV " << i << " IS NOT COVERED BY ANY OF THE TAREGET CHECKING IF CAN BE REMOVED" << endl;
            int x=checkconn(uav,i,ua);
            if (x == 0)
                cout << "the uav "<<x<<" cannot be removed " << endl;
            else
            {
                cout << "the uav "<<x<<"  can be removed" << endl;                
                uav[i].id = uav[i].id - 1;
                for (int g = i+1 ; g <= ua; g++)
                {
                    vector<int> d = coveringuav(g);
                    if (d.size() != 0)
                    {
                        for (int h = 0; h <d.size(); h++)
                        {
                            target[d[h]].coveruav = target[d[h]].coveruav - 1;
                            cout << " the cover of target " << d[h] << " has been updated to uav" << target[d[h]].coveruav<< endl;
                        }
                    }

                    uav[g].id = uav[g].id - 1;
                     if(g==i+1)
                         uav[i + 1].parent = uav[i].parent;
                     else
                     {
                         if (uav[g].parent > uav[i + 1].parent)
                             uav[g].parent = uav[g].parent - 1;
                     }
                }
                uav.erase(uav.begin() + (i));
                ua -= 1;
                
            }
            for (int i = 1; i <= ua; i++)
                cout << "uav " << uav[i].id << " at pos" << uav[i].pos[0] << " with parent " << uav[i].parent << endl;
    }
}
    cout << " THE REMAING UAVS ARE" << endl;
    for (int i = 1; i <= ua; i++)
    {
        cout << "UAV " << i << "AT (" << uav[i].pos[0] << "," << uav[i].pos[1] << "," << uav[i].pos[2] << ")" << " OF RADIUS " << uav[i].radius << " ";
        vector<int> d =coveringuav(i);
        for(int l=0;l<d.size();l++)
        cout<<"  COVERING TARGET " <<d[l]<<" WHICH IS AT " <<    target[d[l]].position[0]<<endl;
        cout << endl;
    }
} 

//Method to update the positions of the targets
void updatetarget(int n)
{

    int  x, y;
        if (n <= t)
        {
            cout << "ENTER THE NEW POSITION OF THE TARGET " << endl;
            cin >> x; cin >> y;
            cout << " THE TARGET (" << target[n].position[0] << " , " << target[n].position[1] << " ) IS BEING UPDATED " << endl;
            target[n].position[0] = x;
            target[n].position[1] = y;
            cout << "UPDATED TARGET " << n << " TO THE POSITION (" << x << "," << y << ")" << endl;
            areas();
            checkcover();
            cout << " the uavs are " << endl;
            for (int p = 1; p <= ua; p++)
            {
                vector<int> d = coveringuav(p);
                for(int o=0;o<d.size();o++)
                cout << " uav " << p << " at position " << uav[p].pos[0] << " COVERING TARGET " << d[o] << " which is at " << target[d[o]].position[0] << endl;
            }rmuav();
        }
        else
            cout << "THIS TARGET DOES NOT EXISTS" << endl;
}
void rmv(int x)
{
    int fl = 0,t=0;
    for (int i = 1; i <= t; i++)
    {
        if (target[i].coveruav == x)
            fl++;
    }
    int first = 0, last = 0;
    if (uav[x].parent == 0)
    {
        cout << x <<" at "<<uav[x].pos[0]<<" is the first uav and can be removed indepandently" << endl;
        first = 1;
    }
    int zz = 0;
    for (int j = 1; j <= ua; j++)
    {
        if (uav[j].parent == x)
        {
            t = j; zz++;
        }

    }
    if (zz == 0)
    {
        cout << x << " at " << uav[x].pos[0] << " is the last node and can be removed independently" << endl;
        last = 1;
    }
    int p = uav[x].parent;
    double s = sqrt(pow((uav[t].pos[0] - uav[p].pos[0]), 2) + pow(((uav[t].pos[1]) - (uav[p].pos[1])), 2) + pow(((uav[t].pos[2]) - (uav[p].pos[2])), 2));
    cout <<" distance between uav "<<uav[t].id<<" and "<<uav[p].id<<" is "<< s << endl;
    //cout << " fl is " << fl;
    if (fl ==0 && s <=150 || (first ==1 && fl == 0) || (last ==1 &&fl == 0))

    {
        cout << " the uav " <<x<< " at " << uav[x].pos[0] << " can be removed" << endl;
        uav[x].id = uav[x].id - 1;
        for (int g = x + 1; g <= ua; g++)
        {
            vector<int> d = coveringuav(g);
            if (d.size() != 0)
            {
                for (int h = 0; h < d.size(); h++)
                {
                    target[d[h]].coveruav = target[d[h]].coveruav - 1;
                    cout << " the cover of target " << d[h] <<"at pos "<<target[d[h]].position[0]<< " has been updated to uav" << target[d[h]].coveruav<<" at pos "<<uav[target[d[h]].coveruav].pos[0] << endl;
                }
            }

            uav[g].id = uav[g].id - 1;
            if (g == x + 1)
                uav[x + 1].parent = uav[x].parent;
            else
            {
                if (uav[g].parent > uav[x + 1].parent)
                    uav[g].parent = uav[g].parent - 1;
            }
        }
        uav.erase(uav.begin() + (x));
        ua -= 1;

        for (int i = 1; i <= ua; i++)
            cout << "uav " << uav[i].id << " at pos" << uav[i].pos[0] << " with parent " << uav[i].parent << " at pos" << uav[uav[i].parent].pos[0] << endl;

    }
    else
        cout << "  the uav "<<x<<" at pos "<<uav[x].pos[0] <<" cannot be removed" << endl;
}
// extension of the project minimizing the number of uavs by moving them and taking to account the connectivity and target covering
void adjustuav()
{
    for (int k = 1; k <= ua; k++)
    {
        vector<int> d = coveringuav(k); int l = 0; uavs temp; int f = 0, c = 0; vector<int> news; vector<int> m;
        cout<<d.size()<<endl;
        temp.pos[0] = uav[k].pos[0]; temp.pos[1] = uav[k].pos[1]; temp.pos[2] = uav[k].pos[2]; temp.radius = uav[k].radius;
        for (int i = ar.min_x; i <= ar.max_x; i++)
            {
                for (int j = ar.min_y; j <= ar.max_y; j++)
                {
                    if (l == 0)
                    {

                    temp.pos[0] = i; temp.pos[1] = j;
                    for (int h = 1; h <= t; h++)
                    {
                        f = 0;
                        if ((((((target[h].position[0]) <= (temp.pos[0] + temp.radius)) && ((target[h].position[0]) >= (temp.pos[0]))) || (((target[h].position[0]) >= (temp.pos[0] - temp.radius)) && ((target[h].position[0]) <= (temp.pos[0])))) && ((((target[h].position[1]) <= (temp.pos[1] + temp.radius)) && (target[h].position[1]) >= (temp.pos[1])) || (((target[h].position[1]) >= (temp.pos[1] - temp.radius)) && (target[h].position[1]) <= (temp.pos[1])))))
                        {
                            f += 1;
                            for (int g = 0; g < d.size(); g++)
                            {
                                
                                if (target[d[g]].position[0] != target[h].position[0] && target[d[g]].position[1] != target[h].position[1])
                                {
                                    
                                    if ((((((target[d[g]].position[0]) <= (temp.pos[0] + temp.radius)) && ((target[d[g]].position[0]) >= (temp.pos[0]))) || (((target[d[g]].position[0]) >= (temp.pos[0] - temp.radius)) && ((target[d[g]].position[0]) <= (temp.pos[0])))) && ((((target[d[g]].position[1]) <= (temp.pos[1] + temp.radius)) && (target[d[g]].position[1]) >= (temp.pos[1])) || (((target[d[g]].position[1]) >= (temp.pos[1] - temp.radius)) && (target[d[g]].position[1]) <= (temp.pos[1])))))
                                    {
                                        f++;
                                        //cout << " when uav " << k << " is at pos " << temp.pos[0] << " , " << temp.pos[1] << endl;
                                        //cout << " covering target " << " at pos " << target[h].position[0] << "  and " << " at position " << target[d[g]].position[0] << endl;
                                        //cout << "can cover target also" << h << endl;
                                        m.push_back(h);
                                    }
                                }
                            }

                            if (f > d.size())
                            {   
                                cout << "the value of f is " << f << endl;
                                for (int s = 0; s < m.size(); s++)
                                {
                                    uav[k].pos[0] = temp.pos[0]; uav[k].pos[1] = temp.pos[1]; uav[k].pos[2] = temp.pos[2];
                                    uav[k].radius = temp.radius;
                                    if(target[m[s]].coveruav != k)
                                    rmv(target[m[s]].coveruav);
                                    d.push_back(m[s]);
                                    target[m[s]].coveruav =target[d[0]].coveruav;
                                    //cout << " the uav " <<k<<" at pos "<<uav[k].pos[0]<<" can cover more targets " << m[s] <<" at pos "<<target[m[s]].position[0]<<endl;
                                                                    
                                }
                                l = 1;
                            }
                        }

                    }
                }
            }
        }
    }
    cout << "THE REMAINING UAVS ARE " << endl;
    for (int y = 1; y <= ua; y++)
    {
        cout << "uav "<<uav[y].id << " at pos " << uav[y].pos[0] << " ," << uav[y].pos[1] << " , " << uav[y].pos[2] << " with radius " << uav[y].radius << endl;
        vector<int> d = coveringuav(y);
        for (int h = 0; h < d.size(); h++)
            cout << " it is covering the target " << target[d[h]].id << " at pos " << target[d[h]].position[0] << endl;
    }
}
int main()
{    
    int u = 0; char o,w;
    //Adding targets
    do {
        cout << "ENTER THE TARGET" << endl;
        t += 1;
        addtarget(t);
        cout << "DO YOU WANT TO ADD MORE TARGET " << endl;
        cin >> o;
    } while (o == 'Y' || o == 'y');

    //placing uav to the position of the first target
    placeuav();
    checkcover();
    cout << "the uavs are " << endl;
    for (int i = 1; i <= ua; i++)
    {
        cout << "uav " << i << " at position " << uav[i].pos[0] << endl;
    }
    int n; char l;
    //upadate the position of the target
    cout << "DO YOU WANT TO UPDATE ANY TARGETS POSITION" << endl;
    cin >> w;
    if (w == 'y' || w == 'Y')
    {
        do {
            cout << "WHICH TARGET TO UPDATE " << endl;
            cin >> n;
            updatetarget(n);
            cout << "DO YOU WANT TO UPDATE MORE TARGETS POSITION" << endl;
            cin >> l;
        } while (l == 'y' || l == 'Y');

    }
    adjustuav();
    //checking for obstructions if found increase the height of the uav 
    for (int i = 1; i <= t; i++)
    {
        if (target[i].id != target[i].coveruav)
            checkobstruction(target[i].coveruav, target[i].id);
    }
    
    _getch();
    return 0;
}

