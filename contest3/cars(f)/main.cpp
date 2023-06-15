#include <iostream>
#include <vector>
#include <set>
#include "bits/stdc++.h"

using std::cin;
using std::cout;
using std::set;
using std::vector;
using std::pair;

typedef long long ll;
int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, k, p;
    cin >> n >> k >> p;
    vector<ll> q(p, 0);
    for (ll i = 0; i < p; ++i) {
        cin >> q[i];
        --q[i];
    }

    vector<pair<ll, vector<ll>>> cars(n, {0, {}});// на i-ой позиции стоит массив с вхождениями i-ой машинки (уже отсортированными)

    for (ll i = 0; i < p; ++i) {
        cars[q[i]].second.push_back(i);
    }
    for (ll i = 0; i < n; ++i) {// просто маркер конца
        cars[i].second.push_back(LLONG_MAX);
    }

    set<ll> floor;
    set<pair<ll, ll>> next_occurrences_of_current_car;

    ll ans = 0;
    for (ll i = 0; i < p; ++i) {

        if (floor.find(q[i]) != floor.end()) {
            pair<ll, vector<ll>>& p = cars[q[i]];

            auto next_occur = next_occurrences_of_current_car.find( { p.second[p.first], q[i] } );
            while(p.second[p.first] <= i) {
                ++p.first;
            }
            next_occurrences_of_current_car.erase(next_occur);
            next_occurrences_of_current_car.insert( { p.second[p.first], q[i] } );
            continue;
        }

        if (floor.size() >= k) {// кладем на полку самую дальнюю машинку
            ll x = (--next_occurrences_of_current_car.end())->second;
            floor.erase(x);
            next_occurrences_of_current_car.erase(--next_occurrences_of_current_car.end());
        }
        floor.insert(q[i]);

        pair<ll, vector<ll>>& p = cars[q[i]];
        while (p.second[p.first] <= i) {
            ++p.first;
        }
        next_occurrences_of_current_car.insert({ p.second[p.first], q[i] });
        ans++;
    }

    cout << ans << '\n';

    return 0;
}