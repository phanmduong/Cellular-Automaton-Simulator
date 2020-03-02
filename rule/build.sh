#! /bin/bash
g++ -dynamiclib -flat_namespace ../cell.cpp ../rule.cpp ../state.cpp user_rule.cpp -o rule.so 
