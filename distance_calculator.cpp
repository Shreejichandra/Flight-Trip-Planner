#include <bits/stdc++.h>
#include <fstream>

using namespace std;
long double toRadians(const long double degree)
{
        long double one_deg = (M_PI) / 180;
        return (one_deg * degree);
}

long double calculate_distance(unordered_map<string, pair<double, double>> &m, string city_from, string city_to)
{
        // Convert the latitudes
        // and longitudes
        // from degree to radians.
        long double lat1 = toRadians(m[city_from].second);
        long double long1 = toRadians(m[city_from].first);
        long double lat2 = toRadians(m[city_to].second);
        long double long2 = toRadians(m[city_to].first);

        long double dlong = long2 - long1;
        long double dlat = lat2 - lat1;

        long double ans = pow(sin(dlat / 2), 2) +
                          cos(lat1) * cos(lat2) *
                              pow(sin(dlong / 2), 2);
        //using the formula we calculate the distance

        ans = 2 * asin(sqrt(ans));

        long double R = 6371;

        ans = ans * R;

        return ans;
}

int main()
{
        ifstream fin;
        fin.open("cities_distance.txt", ios::in);
        unordered_map<string, pair<double, double>> m;
        // we are using this map to store the city and langitute and latitude
        string name_of_city;
        float longi;
        float lati;
        while (fin)
        {
                fin >> name_of_city;
                fin >> longi;
                fin >> lati;
                m[name_of_city] = {longi, lati};
        }
        /*for(auto itr = m.begin();itr!= m.end();itr++)
        {
                cout<<itr->first<<" -> "<<itr->second.first<<" "<<itr->second.second<<"\n";

        }
        // used to print the values in the graph
        */
        fin.close();
        ifstream fin_source;
        fin_source.open("source_dest_cost.txt", ios::in);
        //here we have opened another file to find which cities have link
        ofstream fout;
        fout.open("dataset.txt");
        // the output file
        string city_from;
        string city_to;
        int cost_from_to;
        long double ans;
        /*
         * this loop reads the city which have the flights in common and
         * the cost
         * we then compute the distance between them using 
         * langitute and longitude
         * then we create another loop */

        while (fin_source)
        {
                fin_source >> city_from;
                fin_source >> city_to;
                fin_source >> cost_from_to;
                ans = calculate_distance(m, city_from, city_to);
                fout << city_from << " " << city_to << " " << cost_from_to << " " << (int)ans << endl;
        }
        fin_source.close();
        fout.close();
        cout << " ***The main file is created*** \n";
        return 0;
}
