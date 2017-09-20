#include<iostream>
#include<fstream>
#include "MersenneTwister.h"
#include<time.h>
#include<math.h>
#include<strings.h>

using namespace std;

int s = 0;
MTRand M(s);


int main()
{
    s = (int)time(0);
    M.seed(s);
    long long x=0,i,j,k;
    long long steps,walks,arr,approx,multiples,range;
    ofstream f1;
    steps = 1000;
    int prob_r = 50;//I shall generate a random number between 0 and 99 and check if it's greater than prob_r so that I can generate a probability of half of the particle moving left or right.
    walks = 100000;
    multiples = 1;
    int rwall = 900;//postion of reflecting wall on right
    int lwall = -900;//position of reflecting wall on left
    int wall_absorb_r = 50;//position of aborbing wall on right
    int wall_absorb_l = -1500;//position of absorbing wall on left
    int wall_partial_r = 500;//position of partially abosrbing wall on right
    int wall_partial_l = -50;//position of partially absorbing wall on left
    int prob_absorb = 20;//percentage probability of particle being absorbed at partial
    int r;
    f1.open("Abso.txt");
    long its=steps;

for(int z=0;z<=5;z++)
{
    f1<<its<<"\n";
    cout<<"\nRunning for "<<its;
    double navg =0.00,nsqavg=0.00;
    arr = 2*its+1;
    long long A[arr];
    long long absorbed_r = 0, absorbed_l = 0;//variables to count number of particles absorbed at left and right walls
    long long partial_absorbed_r = 0, partial_absorbed_l = 0;//variables to count numbe of particles partially absorbed at left and right walls
    int flag = 0;//flag to check conditions whhich wall particles has reached or whether particle is at a normal point on the lattice
    approx = sqrt(its)*4;//just a variable to make a suitable range of lattice points to plot the histogram on
    for(i=0;i<arr;i++) A[i] = 0;//initializing the frequency array

    for(i=0;i<walks;i++)
    {
        x = 0;//initializing position to 0
        flag=0;
        for(j=0;j<its;j++)//loop to set number of particles
        {
            if(flag==0)//coniditon that particle is at a normal point so procede with a normal random walk
            {
             r = M.randInt(99);

            if(r<prob_r) x++;
            else x--;
            }
            if(flag==1)//condition that particle is at a left reflecting wall so move right
            {
                x++;
                flag = 0;
            }
            if(flag==2)//condition that particle is at a right reflecting wall so move left
            {
                x--;
                flag = 0;
            }
            if(flag==3)//condition that particle is at an absorbing wall so terminate walk
            {
                if(x>0) absorbed_r++;
                else absorbed_l++;
                break;
            }
            if(flag==4)//condition that particle is at a partially absorbing wall
            {
                r = M.randInt(99);
                if(r<prob_absorb)//if the random number generated is less than probability of getting absorbed
                {
                    if(x>0) partial_absorbed_r++;//this signifies that particles is at right partially absorbing wall so count of that goes up
                    else partial_absorbed_l++;//this signigies that particles is at left patially absorbing wall so count of that goes up
                    break;
                }
                else//comtinue with regular random walk
                {
                    r = M.randInt(99);
                    if(r>prob_r) x++;
                    else x--;
                }
                flag = 0;
            }
            if(x>=rwall) flag = 2;//if particles is at right reflecting wall
            if(x<=lwall) flag = 1;//if particles is at left reflecting wall
            if(x>=wall_absorb_r || x<=wall_absorb_l) flag = 3;//if particle is at any of the absorbing walls
            if(x==wall_partial_r || x==wall_partial_l) flag = 4;//if particle is at any of the partially absoring walls

        }
        if(flag!=3&&flag!=4)
        A[(x+its-1)]++;//increment corresponding frequencies for all cases except when particle is at absorbing wall or partially absorbing wall,this is done so that the histogram does not have a rather awkwardly high bar at the position of the absorbing wall

    }


    for(i=0;i<arr;i++)
    {
        navg = navg + (A[i]*(i-its+1));//calculating the total displacement of all particles at the end of their walks
        nsqavg = nsqavg + ((i-its+1)*A[i]*(i-its+1));//calculating the total square of the displacement of all the particles at the end of their walks
    }
    navg = navg/walks;//average displacement
    nsqavg = nsqavg/walks;//average of square of displacement
    if(its>=wall_absorb_l)
    {
        cout<<"\n Percent Absorbed Left = "<<((double)absorbed_l/(double)walks)*100;
    }
    if(its>=wall_absorb_r)
    {
        cout<<"\n Percent Absorbed Right = "<<((double)absorbed_r/(double)walks)*100;

    }
    if(its>=wall_partial_r)
    {
        cout<<"\n Partially absorbed at right wall : "<<((double)partial_absorbed_r/(double)walks)*100;
    }
    if(its>=wall_partial_l)
    {
        cout<<"\n Partially absorbed at left  wall : "<<((double)partial_absorbed_l/(double)walks)*100;
    }

        for(k=its-approx;k<=its+approx;k=k++)//running lattice points from where the frequency is approximately just above zero to the other side where it jst falls to zero
    {
        if(A[k]!=0)//writing into file only when frequency is non zero
        {
        f1<<k-its+1<<"\t"<<(double)A[k]/(double)walks<<"\n";//writing position and corresponding frequency via the frequency array into the file
        }
    }
    f1<<"\n\n";
    cout<<"\n<n> = "<<navg;
    cout<<"\n<n^2> = "<<nsqavg;
    its = its + steps;//just to generate multiple graphs with different number of steps in each walk
}
    f1.close();
    return 0;
}
