#pragma once

#include <string>
#include <vector>

using std::vector;
using std::string;

void Split(const string& from, vector<string>& to, char	sep);
void Split(const string& from, vector<string>& to, const string& sep);

void Join(const vector<string>& from, string& to, char sep);
void Join(const vector<string>& from, string& to, const string& sep);