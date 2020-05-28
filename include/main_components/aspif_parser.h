#ifndef ASPIF_PARSER_H
#define ASPIF_PARSER_H
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <unordered_map>
#include <math.h>
#include "aspif_minimize_statement.h"
#include "aspif_rule_statement.h"

namespace aspsio {
    
    // A specific implementation of a Parser that interpretates
    // the "aspif" format
    
    class AspifParser {
        private:
            std::list<std::string> *input_encoding;

            // Each list of rules contains only rules rewritten by 
            // the SAME Rewriting method (a rule can exist in two or more lists)
            std::vector<std::list<std::shared_ptr<AspifStatement>>> *rules_to_optimize;

            //Patterns of the fresh predicates generated by a Rewriting 
            std::vector<std::string> *patterns_to_match;

            // The first element is the predicate's id (key value)
            // The second element is the type of Rewriting
            std::unordered_map<int, int> aux_predicates;

            // An Hash Table of auxiliar predicates used to save their
            // occurrences in rules
            std::vector<std::unordered_map<int, std::shared_ptr<AspifLiteral>>> aux_predicates_instances;

            std::list<std::string>::iterator line_to_parse;

            //  Option used to know that rules with need of duplication
            //  will not be reversed
            bool optimize_reversing_activated;

            void SaveAuxiliarPredicates();
            void SaveRulesToOptimize();
            void ParseRuleStatement(std::string input_line, std::string &full_input_line);
            void ParseMinimizeStatement(std::string input_line, std::string &full_input_line);
            void StoreSingleRuleStatement(std::string input_line, std::string &full_input_line, const int &head_type);
            void StoreSingleMinimizeStatement(std::string input_line, std::string &full_input_line, const int &priority);

        public:
            AspifParser(std::list<std::string> &input_data, std::vector<std::list<std::shared_ptr<AspifStatement>>> &rules_sets, 
                    std::vector<std::string> &pattern_set);
            virtual void StartAnalysis();
            void ActivateOptimizeReversing(){ optimize_reversing_activated = true; }
            void AddReverseParsingOption(const std::string &pattern);
            std::vector<std::unordered_map<int, std::shared_ptr<AspifLiteral>>>& GetAuxPredicatesInstances(){
                return aux_predicates_instances;
            }

    };
}

#endif