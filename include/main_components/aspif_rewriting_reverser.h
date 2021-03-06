#ifndef ASPIF_REWRITING_REVERSER_H
#define ASPIF_REWRITING_REVERSER_H
#include "aspif_statement.h"
#include <list>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_map>

namespace aspsio {

    //  A specific "aspif" format class that does a Reverse 
    //  of a rule that was rewritten during the grounding phase
    class AspifRewritingReverser {

        protected:
            std::unordered_map<int, std::list<std::shared_ptr<AspifStatement>>> *rules_to_reverse;
            std::vector<std::unordered_map<int, std::list<std::shared_ptr<AspifStatement>>>> *all_rules_to_reverse;
            std::unordered_map<int, std::shared_ptr<AspifLiteral>> *aux_predicates_instances;
            std::list<std::string> *input_encoding;
            bool duplicate_checking;
            bool limit_body;
            virtual void DoRulesAdjustments(std::shared_ptr<AspifLiteral> auxiliar_to_adjust);
            int CountDuplicate(const std::string &rule, std::vector<std::string> &rules);
            int CountDuplicate(const std::string &rule, std::shared_ptr<AspifLiteral> auxiliar);

        public:
            AspifRewritingReverser(std::unordered_map<int, std::list<std::shared_ptr<AspifStatement>>> &rules_set, std::unordered_map<int, std::shared_ptr<AspifLiteral>> &_aux_predicates_instances, std::list<std::string> &_input_encoding, const bool &aux_limit_body, std::vector<std::unordered_map<int, std::list<std::shared_ptr<AspifStatement>>>> &all_rules_sets);
            virtual int DoReverse();
            int RemoveUselessPredicates(std::unordered_map<int, int> &removed_predicates);
            void DisableDuplicateChecking(){ duplicate_checking = false; }

    };
}

#endif