#include <bits/stdc++.h>
using namespace std;

class Rollnumber {
public:
    string r = "0";

    void createroll(string x) {
        r = x;
    }

    void print() {
        cout << r << endl;
    }

    static bool compare(const Rollnumber &a, const Rollnumber &b) {
        return a.r < b.r;
    }
};

class Faculty {
public:
    string name = "0";
    bool permanent = 0;
    set<string> hostel;
    vector<Rollnumber> facadfor;
    vector<Rollnumber> BTPGuidefor;
    vector<Rollnumber> DDPGuidefor;
    vector<Rollnumber> TAs;

    void addfaculty(string n, bool p) {
        name = n;
        permanent = p;
    }

    void printname() {
        cout << name << endl;
    }

    friend class Btech;
    friend class DualDegree;
    friend class NITR;
};

class DualDegree {
public:
    Rollnumber roll;
    string hostel = "0";
    Faculty facad;
    float cgpa = -1;
    Faculty DDPGuide;
    bool projectee = 0;
    bool TA = 0;
    Faculty TASupervisor;

    void addstudent(Rollnumber r, string h, Faculty &f, float cgp) {
        roll = r;
        hostel = h;
        facad = f;
        cgpa = cgp;
        f.facadfor.push_back(roll);
    }

    string getHostel() { return hostel; }
    Faculty getFacad() { return facad; }
    float getcgpa() { return cgpa; }
    Rollnumber getroll() { return roll; }

    void changeHostel(string newhostel) { hostel = newhostel; }

    void setDDPGuide(Faculty &f) {
        DDPGuide = f;
        f.DDPGuidefor.push_back(roll);
        projectee = 1;
    }

    void setTASupervisor(Faculty &f) {
        TA = true;
        TASupervisor = f;
        f.TAs.push_back(roll);
    }

    friend class NITR;
};

class Btech {
public:
    Rollnumber roll;
    string hostel = "0";
    Faculty facad;
    float cgpa = -1;
    Faculty BTPGuide;
    bool projectee = 0;

    void addstudent(Rollnumber r, string h, Faculty &f, float cgp) {
        roll = r;
        hostel = h;
        facad = f;
        cgpa = cgp;
        f.facadfor.push_back(r);
    }

    string getHostel() { return hostel; }
    Faculty getFacad() { return facad; }
    float getcgpa() { return cgpa; }
    Rollnumber getroll() { return roll; }

    void changeHostel(string newhostel) { hostel = newhostel; }

    void setBTPGuide(Faculty &f) {
        BTPGuide = f;
        f.BTPGuidefor.push_back(roll);
        projectee = 1;
    }

    friend class NITR;
};

class NITR {
private:
    vector<Rollnumber> students;
    vector<Btech> Btechies;
    vector<DualDegree> DDs;
    vector<Faculty> faculty;
    vector<string> hostels;

public:
    void create(int n, int m, int h) {
        srand(static_cast<unsigned>(time(0)));

        unordered_set<string> unique;

        // hostels
        while (hostels.size() < h) {
            int nameLength = 1 + rand() % 10;
            string name;
            for (int i = 0; i < nameLength; ++i) {
                name += 'a' + rand() % 26;
            }
            if (unique.find(name) == unique.end()) {
                hostels.push_back(name);
                unique.insert(name);
            }
        }
        unique.clear();

        // faculty
        while (faculty.size() < m) {
            int nameLength = 1 + rand() % 14;
            string name;
            for (int i = 0; i < nameLength; ++i) {
                name += 'a' + rand() % 26;
            }
            bool p = rand() % 2;
            if (unique.find(name) == unique.end()) {
                Faculty f;
                f.addfaculty(name, p);
                faculty.push_back(f);
                unique.insert(name);
            }
        }
        unique.clear();

        // students
        while (students.size() < n) {
            string roll;
            for (int i = 0; i < 7; ++i) {
                roll += '0' + rand() % 10;
            }
            Rollnumber r;
            if (unique.find(roll) == unique.end()) {
                r.createroll(roll);
                students.push_back(r);
                unique.insert(roll);
            }

            string hostel = hostels[rand() % hostels.size()];
            Faculty &facada = faculty[rand() % faculty.size()];
            float gpa = (rand() % 1001) / 100.00;

            int degree = rand() % 2;
            if (degree == 1) {
                Btech b;
                b.addstudent(r, hostel, facada, gpa);
                Btechies.push_back(b);
            } else {
                DualDegree d;
                d.addstudent(r, hostel, facada, gpa);
                DDs.push_back(d);
            }
        }
    }

    void assignBTP() {
        sort(Btechies.begin(), Btechies.end(), [&](Btech &a, Btech &b) {
            return a.getcgpa() < b.getcgpa();
        });

        int j = 0;
        for (int i = 0; i < faculty.size() && j < Btechies.size(); i++) {
            if (faculty[i].permanent) {
                int pro = rand() % 3;
                if (pro == 1) {
                    Btechies[j].setBTPGuide(faculty[i]);
                    faculty[i].hostel.insert(Btechies[j].hostel);
                    j++;
                } else if (pro == 2) {
                    Btechies[j].setBTPGuide(faculty[i]);
                    faculty[i].hostel.insert(Btechies[j].hostel);
                    j++;
                    if (j < Btechies.size()) {
                        Btechies[j].setBTPGuide(faculty[i]);
                        faculty[i].hostel.insert(Btechies[j].hostel);
                        j++;
                    }
                }
            }
        }
    }

    void assignDDP() {
        sort(DDs.begin(), DDs.end(), [&](DualDegree &a, DualDegree &b) {
            return a.getHostel() < b.getHostel();
        });

        int j = 0;
        for (int i = 0; i < faculty.size() && j < DDs.size(); i++) {
            if (faculty[i].permanent) {
                int pro = rand() % 3;
                if (pro == 1) {
                    DDs[j].setDDPGuide(faculty[i]);
                    faculty[i].hostel.insert(DDs[j].hostel);
                    j++;
                } else if (pro == 2) {
                    DDs[j].setDDPGuide(faculty[i]);
                    faculty[i].hostel.insert(DDs[j].hostel);
                    j++;
                    if (j < DDs.size()) {
                        DDs[j].setDDPGuide(faculty[i]);
                        faculty[i].hostel.insert(DDs[j].hostel);
                        j++;
                    }
                }
            }
        }
    }

    void assignTA() {
        int i = 0, j = 0;
        for (; i < faculty.size(); i++) {
            if (j + 4 >= DDs.size()) break;
            for (int k = 0; k < 5 && j < DDs.size(); k++, j++) {
                DDs[j].setTASupervisor(faculty[i]);
            }
        }
        if (i < faculty.size()) {
            for (; j < DDs.size(); j++) {
                DDs[j].setTASupervisor(faculty[i]);
            }
        }
    }

    bool check() {
        for (int i = 0; i < faculty.size(); i++) {
            if (faculty[i].BTPGuidefor.size() > 2 ||
                faculty[i].DDPGuidefor.size() > 2 ||
                faculty[i].TAs.size() > 5) {
                return false;
            }
        }
        return true;
    }

    float percentage() {
        int size = Btechies.size() + DDs.size();
        int same = 0;
        for (int i = 0; i < DDs.size(); i++) {
            if (DDs[i].DDPGuide.name == DDs[i].TASupervisor.name) same++;
        }
        return (size == 0) ? 0.0 : (float(same) / size);
    }

    void noguide() {
        for (int i = 0; i < Btechies.size(); i++) {
            if (Btechies[i].projectee == 0) Btechies[i].roll.print();
        }
        for (int i = 0; i < DDs.size(); i++) {
            if (DDs[i].projectee == 0) DDs[i].roll.print();
        }
    }

    vector<Faculty> maxhostel() {
        vector<Faculty> max;
        int maxnum = 0;
        for (int i = 0; i < faculty.size(); i++) {
            int diff = faculty[i].hostel.size();
            if (diff > maxnum) maxnum = diff;
        }
        for (int i = 0; i < faculty.size(); i++) {
            if (faculty[i].hostel.size() == maxnum) max.push_back(faculty[i]);
        }
        return max;
    }

    void proll() {
        cout << "Rollwise:" << endl;
        sort(students.begin(), students.end(), Rollnumber::compare);
        for (int i = 0; i < students.size(); i++) {
            students[i].print();
        }
    }

    void pguidename() {
        cout << "Guidenamewise:" << endl;
        cout << endl << "Btech:" << endl;

        sort(Btechies.begin(), Btechies.end(), [&](Btech &a, Btech &b) {
            if (a.projectee && b.projectee) {
                if (a.BTPGuide.name != b.BTPGuide.name)
                    return a.BTPGuide.name < b.BTPGuide.name;
                return a.roll.r < b.roll.r;
            }
            if (a.projectee) return true;
            if (b.projectee) return false;
            return a.roll.r < b.roll.r;
        });

        for (int i = 0; i < Btechies.size(); i++) {
            Btechies[i].roll.print();
        }

        cout << endl << "DualDegree:" << endl;
        sort(DDs.begin(), DDs.end(), [&](DualDegree &a, DualDegree &b) {
            if (a.projectee && b.projectee) {
                if (a.DDPGuide.name != b.DDPGuide.name)
                    return a.DDPGuide.name < b.DDPGuide.name;
                return a.roll.r < b.roll.r;
            }
            if (a.projectee) return true;
            if (b.projectee) return false;
            return a.roll.r < b.roll.r;
        });

        for (int i = 0; i < DDs.size(); i++) {
            DDs[i].roll.print();
        }
    }

    void phostel() {
        cout << "Hostelwise:" << endl;
        cout << endl << "Btech:" << endl;
        sort(Btechies.begin(), Btechies.end(), [&](Btech &a, Btech &b) {
            if (a.hostel != b.hostel) return a.hostel < b.hostel;
            return a.roll.r < b.roll.r;
        });
        for (int i = 0; i < Btechies.size(); i++) {
            Btechies[i].roll.print();
        }

        cout << endl << "DualDegree:" << endl;
        sort(DDs.begin(), DDs.end(), [&](DualDegree &a, DualDegree &b) {
            if (a.hostel != b.hostel) return a.hostel < b.hostel;
            return a.roll.r < b.roll.r;
        });
        for (int i = 0; i < DDs.size(); i++) {
            DDs[i].roll.print();
        }
    }
};

int main() {
    int n, m, h;
    cin >> n >> m >> h;
    NITR community;
    community.create(n, m, h);
    community.assignBTP();
    community.assignDDP();
    community.assignTA();

    if (community.check()) cout << "Satisfied" << endl;
    else cout << "Not satisfied" << endl;

    cout << community.percentage() << endl;

    vector<Faculty> max = community.maxhostel();
    for (int i = 0; i < max.size(); i++) {
        max[i].printname();
    }

    cout << endl;
    community.proll();
    cout << endl;
    community.pguidename();
    cout << endl;
    community.phostel();
    cout << endl;
    cout << "No guide:" << endl;
    community.noguide();
}
