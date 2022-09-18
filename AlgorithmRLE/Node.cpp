#include "Node.h"

using namespace std;

struct BestSolution { 
    int num_;
    int position_;

    BestSolution(int num, int position) {
        num_ = num;
        position_ = position;
    }
};

Node::Node(std::string base, int num_repeats)
{
    base_ = base;
    num_repeats_ = num_repeats;
    for (int size_string = base.size() / 2; size_string > 0; size_string--) {
        int max_offset = base.size() - 2 * size_string;
        BestSolution best_solution(0, 0);
        for (int offset = 0; offset <= max_offset; offset++) { 
            int num = 1;
            string base_string = base.substr(offset, size_string);

            while (num * size_string + offset == base.find(base_string, num * size_string + offset)) {
                num++;
            }
            if (num > 1) {
                if (num > best_solution.num_) {
                    best_solution.num_ = num;
                    best_solution.position_ = offset;
                }
            }
        }

        if (best_solution.num_ != 0) {
            if (best_solution.position_ > 0) {
                child_.push_back(Node(base.substr(0, best_solution.position_), 1));
            }
            child_.push_back(Node(base.substr(best_solution.position_, size_string), best_solution.num_));

            if (best_solution.num_ != child_.at(child_.size() - 1).num_repeats_) {
                child_.clear();
                continue;
            }


            if (base.size() > best_solution.position_ + best_solution.num_ * size_string) {
                child_.push_back(Node(base.substr(best_solution.position_ + best_solution.num_ * size_string, base.size() - best_solution.position_ + best_solution.num_ * size_string), 1));
            }

            if (child_.size() == 1) {
                base_ = child_.at(0).base_;
                num_repeats_ = num_repeats_ * child_.at(0).num_repeats_;
                child_.clear();
                break;
            }

            if (child_.size() == 2) {
                if (child_.at(0).base_ == child_.at(1).base_) {
                    base_ = child_.at(0).base_;
                    num_repeats_ = num_repeats_ * (child_.at(0).num_repeats_ + child_.at(1).num_repeats_);
                    child_.clear();
                }
            }
            else {
                if (child_.at(1).base_ == child_.at(2).base_) {
                    child_.insert(child_.begin() + 1, Node(child_.at(1).base_, child_.at(1).num_repeats_ + child_.at(2).num_repeats_));
                    child_.erase(child_.begin() + 2);
                    child_.erase(child_.begin() + 2);
                }
            }

            break;
        }
    }
}

std::string Node::ReturnAsString()
{
    std::string ans = "";
    if (child_.size() > 0) {
        for (auto it = child_.begin(); it < child_.end(); ++it) {
            ans = ans + it->ReturnAsString();
        }
    }
    else {
        ans = base_;
    }

    if (num_repeats_ > 1) {
        ans = to_string(num_repeats_) + "(" + ans + ")";
    }

    return ans;
}

