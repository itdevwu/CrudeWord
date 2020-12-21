// This project is licensed under Apache License, Version 2.0 http://www.apache.org/licenses/
// Copyright 2020, Zhenglong WU
// Version: 0.1
#include <bits/stdc++.h>
// #include <io.h>
#include <windows.h> // Currently only available on Windows

using namespace std;

struct word
{
    string text;
    int correct;
    int wrong;
    int tot;
    int iter;
    double rate;

    bool operator<(const word &other) const
    {
        if (iter + 2 < other.iter)
            return false; // 轮数大的放在后面
        else
            return (rate < other.rate); // 大根堆错误率大的放前面
    }

    void calc()
    {
        tot = wrong + correct;
        rate = (wrong * 1.0) / (tot * 1.0);
    }

    void init(string x)
    {
        text = x;
        correct = 1;
        wrong = 1;
        tot = 2;
        iter = 0;
        calc();
    }

    void addwrond()
    {
        tot += 1;
        wrong += 1;
        calc();
    }

    void addcorrect()
    {
        tot += 1;
        correct += 1;
        calc();
    }

} tmp;

priority_queue<word, vector<word> > pq;

void read_old()
{
    system("cls");
    string opt;
    cout << "Read old database?(y/n)\n";
    cin >> opt;
    if (opt == "y" || opt == "Y")
    {
        ifstream dbin("db.txt");
        // freopen("db.txt", "r", stdin); // Not working in my environment.
        do
        {
            string word;
            int correct, wrong;

            dbin >> word >> correct >> wrong;
            tmp.init(word);
            tmp.correct = correct;
            tmp.wrong = wrong;
            tmp.calc();
            tmp.iter = tmp.correct + tmp.wrong - 2;

            pq.push(tmp);
        } while (!dbin.eof());
        // freopen("CON", "r", stdin); // Not working in my environment.

        cout << "Old database loaded successfully\n";
    }
}

void read_new()
{
    system("cls");
    string opt;
    cout << "Read new words?(y/n)\n";
    cin >> opt;
    if (opt == "y" || opt == "Y")
    {
        cout << "Loading words\n";

        ifstream fin("list.txt");
        // freopen("list.txt", "r", stdin); // Not working in my environment.
        do
        {
            string word;
            fin >> word;
            tmp.init(word);
            pq.push(tmp);
        } while (!fin.eof());
        // freopen("CON", "r", stdin); // Not working in my environment.
        cout << "Word list loaded successfully\n";
    }
}

void save()
{
    ofstream fout("db.txt");
    while (!pq.empty())
    {
        fout << pq.top().text << " " << pq.top().correct << " " << pq.top().wrong << endl;
        pq.pop();
    }
}

void run()
{
    while (!pq.empty())
    {
        system("cls");
        cout << "\n\nDo you know the word displayed below?\n\n";
        cout << pq.top().text << "\n\n";
        cout << "Please enter y for yes, n for no.\n";
        cout << "Wrong rate:" << pq.top().rate << "\n";

        string opt;
        cin >> opt;

        if (opt == "y" || "opt" == "Y")
        {
            tmp = pq.top();
            tmp.addcorrect();
            tmp.iter++;
            pq.pop();
            pq.push(tmp);
        }
        else if (opt == "n" || "opt" == "N")
        {
            tmp = pq.top();
            tmp.addwrond();
            tmp.iter++;
            pq.pop();
            pq.push(tmp);
            // string cmd = "\"C:\\Program Files\\Firefox Developer Edition\\firefox.exe\"";
            string cmd = "start";
            string url = " https://cn.bing.com/dict/search?q=" + tmp.text;
            cmd += url;
            system(cmd.c_str());
        }
        else if (opt == "save")
        {
            save();
        }
    }
}

signed main()
{

    read_old();

    read_new();

    run();

    return 0;
}