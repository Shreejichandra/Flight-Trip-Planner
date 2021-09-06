#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;
template <typename T>
class Graph
{
    map<T, list<pair<T, pair<int, int>>>> m;

public:
    void addFlight(T start, T end, int cost, int time_taken, bool bidir = true)
    {
        m[start].push_back(make_pair(end, make_pair(cost, time_taken)));
        if (bidir)
        {
            m[end].push_back(make_pair(start, make_pair(cost, time_taken)));
        }
    }
    void print_route()
    { // prints the whole graph

        for (auto i : m)
        {

            cout << i.first << " -> ";
            for (auto j : i.second)
            {
                cout << "(" << j.first << "," << j.second.first << "," << j.second.second << ")";
            }
            cout << endl;
        }
    }
    void min_dist(T source, T arri, string choice)
    {
        // Calculating minimum distance using dijkstras' algorithm.

        map<T, int> dist;
        map<T, T> parent;
        int distance;
        stack<T> path;
        T res;
        T location = arri;
        for (auto i : m)
        {
            dist[i.first] = INT_MAX;
        }
        set<pair<int, T>> s;
        dist[source] = 0;
        parent[source] = "NULL";
        s.insert(make_pair(0, source));
        while (!s.empty())
        {
            auto p = *(s.begin());
            T node = p.second;
            int node_dist = p.first;
            s.erase(s.begin());
            for (auto child : m[node])
            {
                if (choice == "C" or choice == "c")
                    distance = child.second.first;
                else
                    distance = child.second.second;
                if (node_dist + distance < dist[child.first])
                {
                    T dest = child.first;
                    auto f = s.find(make_pair(dist[dest], dest));
                    if (f != s.end())
                    {
                        s.erase(f);
                    }
                    dist[dest] = node_dist + distance;
                    s.insert(make_pair(dist[dest], dest));
                    parent[dest] = node;
                }
            }
        }
        path.push(location);
        while (location != "NULL")
        {
            res = parent[location];
            if (res == "NULL")
                break;
            path.push(res);
            location = res;
        }
        cout << "The cheapest route is: \n";
        while (!path.empty())
        {
            cout << path.top() << "->";
            path.pop();
        }
        cout << "OVER";
        if (choice == "C" or choice == "c")
        {
            cout << "\nThe minimum amount you have to pay to travel from " << source << " " << arri << " is: Rs. ";
            for (auto d : dist)
            {
                if (d.first == arri)
                    cout << d.second << endl;
            }
        }
        else
        {
            int time_reqd;
            for (auto d : dist)
            {
                if (d.first == arri)
                    time_reqd = d.second;
            }
            int hours = time_reqd / 60;
            int mins = time_reqd % 60;
            cout << "\nThe minimum travelling time from " << source << " to " << arri << " is: " << hours << " hrs " << mins << " mins.";
        }
    }
};
const char plane[] =
    "                                       |\\\n\
                         /|            | \\\n\
                        / |            |  \\\n\
                        ---------------------------\n\
                        |         WELCOME           \\\n\
                        |      PLAN YOUR TRIP       /\n\
                        ----------------------------\n\
                        | /           |  /\n\
                        |/            | /\n\
                                      |/\n\
";

const char cities[] =
    "           ---------------------------------------------\n\
                |    CHOICE   |       CITY                 |\n\
                ----------------------------------------------\n\
                |     1.      |      DELHI                       |\n\
                |     2.      |      MUMBAI                   |\n\
                |     3.      |      KOLKATA                  |\n\
                |     4.      |      BANGALORE            |\n\
                |     5.      |      CHENNAI                  |\n\
                |     6.      |      HYDERABAD             |\n\
                |     7.      |      PUNE                         |\n\
                |     8.      |      AHMEDABAD            |\n\
                |     9.      |      SURAT                       |\n\
                |    10.      |      LUCKNOW                |\n\
                |    11.      |      JAIPUR                      |\n\
                |    12.      |      MIRZAPUR                |\n\
                |    13.      |      NAGPUR                    |\n\
                |    14.      |      INDORE                     |\n\
                |    15.      |      VADODARA               |\n\
                |    16.      |      VISAKHAPATNAM     |\n\
                |    17.      |      BHOPAL                     |\n\
                |    18.      |      PATNA                        |\n\
                |    19.      |      LUDHIANA                 |\n\
                |    20.      |      NASIK                        |\n\
                |    21.      |      AURANGABAD          |\n\
                |    22.      |      JABALPUR                 |\n\
                |    23.      |      ALLHABAD                 |\n\
                |    24.      |      SRINAGAR                |\n\
                |    25.      |      AMRITSAR                |\n\
                |    26.      |      GWALIOR                  |\n\
                |    27.      |      RANCHI                     |\n\
                |    28.      |      CHANDIGARH        |\n\
                |    29.      |      MYSORE                |\n\
                |    30.      |      KOTA                      |\n\
                |    31.      |      BAREILLY               |\n\
                |    32.      |      COIMBATORE        |\n\
                |    33.      |      GUWAHATI             |\n\
                |    34.      |      JALANDHAR          |\n\
                |    35.      |      KOCHI                    |\n\
                |    36.      |      GORAKHPUR         |\n\
                |    37.      |      RAURKELA            |\n\
                |    38.      |      MANGALORE         |\n\
                |    39.      |      DURGAPUR           |\n\
                |    40.      |      AJMER                   |\n\
                |    41.      |      BIKANER                |\n\
                |    42.      |      AGARTALA             |\n\
                |    43.      |      UJJAIN                   |\n\
                |    44.      |      JHANSI                  |\n\
                |    45.      |      JAMMU                  |\n\
                |    46.      |      UDAIPUR               |\n\
                |    47.      |      ROHTAK                |\n\
                ---------------------------------------------\n\
";
int main()
{

    vector<string> city;
    ifstream fin;
    fin.open("all_cities.txt", ios::in);
    string place;
    /*
    Created a vector for all cities.
    We pushed the city data from all_cities.txt to vector city.
    */
    while (fin)
    {
        fin >> place;
        city.push_back(place);
    }
    fin.close();

    /*
    Created a graph, named flight_planner.
    Imported data from dataset.txt to create vertices and edges of the graph.
    */
    Graph<string> flight_planner;
    ifstream fin2;
    fin2.open("dataset.txt", ios::in);
    string start, ending;
    int cost;
    int time_taken;
    while (fin2)
    {
        fin2 >> start;
        fin2 >> ending;
        fin2 >> cost;
        fin2 >> time_taken;
        flight_planner.addFlight(start, ending, cost, time_taken);
    }
    //flight_planner.print_route();
    string departure_city, arrival_city, ch, choice;
    int num1, num2;
    printf("%s", plane);
    cout << "\n";

    // DRIVER PROGRAM

    cout << "SELECT DEPARTURE LOCATION: \n";
    printf("%s", cities);
    cout << "YOUR CHOICE:";
    cin >> num1;
    departure_city = city[num1 - 1];
    //cout << departure_city;

    cout << "SELECT ARRIVAL LOCATION: \n";
    printf("%s", cities);
    cout << "YOUR CHOICE:";
    cin >> num2;
    arrival_city = city[num2 - 1];
    //cout << arrival_city;

    cout << "Do you want to optimise your route? (Y/N) \n";
    cin >> ch;
    if (ch == "Y" || ch == "y")
    {
        cout << "Enter C to know the cheapest route and T to know route that takes minimum time: ";
        cin >> choice;

        if (choice == "C" || choice == "c")
            flight_planner.min_dist(departure_city, arrival_city, "C");
        else
            flight_planner.min_dist(departure_city, arrival_city, "T");
    }
    else
        flight_planner.print_route();

    return 0;
}
