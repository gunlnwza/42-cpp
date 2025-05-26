#ifndef VECTOR_MERGE_INSERTION
# define VECTOR_MERGE_INSERTION

# include "ISortStrategy.hpp"
# include <iostream>

class VectorChunk
{
    private:
        int                 key;
        std::vector<int>    data;
        size_t              size;

    public:
        VectorChunk() : key(0), size(0) {}
        ~VectorChunk() {}

        VectorChunk(const std::vector<int>& left_data, const std::vector<int>& right_data) {
            this->key = right_data.back();
            this->data = left_data;
            this->data.insert(this->data.end(), right_data.begin(), right_data.end());
            this->size = left_data.size() + right_data.size();
        }

        VectorChunk(const std::vector<int>& data) {
            this->key = data.back();
            this->data = data;
            this->size = data.size();
        }

        VectorChunk(int data) {
            this->key = data;
            this->data.push_back(data);
            this->size = 1;
        }

        int get_key() const {
            return (this->key);
        }

        std::vector<int> get_data() const {
            return (this->data);
        }

        size_t get_size() const {
            return (this->size);
        }

        bool operator<(const VectorChunk& other) {
            return (this->key < other.key);
        }

        bool operator>(const VectorChunk& other) {
            return (this->key > other.key);
        }

        void divide_into(VectorChunk& lesser, VectorChunk& greater) {
            std::cout << "lesser.data.clear();" << std::endl;
            lesser.data.clear();
            std::cout << "greater.data.clear();" << std::endl;
            greater.data.clear();

            for (std::vector<int>::iterator it = this->data.begin(); it != this->data.end(); ++it) {
                std::cout << *it << " ";
            }
            std::cout << "size_t n = this->size / 2;" << std::endl;
            size_t n = this->size / 2;
            std::cout <<" HI HELLO" << std::endl;
            for (size_t i = 0; i < this->size; ++i)
            {
                if (i < n) {
                    std::cout << "inserting data to lesser" << std::endl;
                    lesser.data.push_back(this->data.at(i));
                }
                else {
                    std::cout << "inserting data to greater" << std::endl;
                    greater.data.push_back(this->data.at(i));
                }
            }
        }
};

class JacobsthalDecreasingSequence
{
    private:
        int a;
        int b;
        int cur;

    public:
        JacobsthalDecreasingSequence() : a(0), b(1), cur(1) {}
        ~JacobsthalDecreasingSequence() {}

        int next() {
            int res;
            int temp;

            if (a < cur && cur <= b)
            {
                res = cur;
                cur--;
            }
            else
            {
                temp = b + 2 * a;
                a = b;
                b = temp;
                cur = b;
                res = b;
            }
            return (res);
        }
};


class VectorMergeInsertion : public ISortStrategy
{
    private:
        std::vector<int> vector;

        void _merge_insertion(std::vector<VectorChunk>& chunks);

    public:
        VectorMergeInsertion();
        VectorMergeInsertion(const VectorMergeInsertion& other);
        VectorMergeInsertion& operator=(const VectorMergeInsertion& other);
        ~VectorMergeInsertion();

        void             copy_numbers(const std::vector<int>& vec);
        std::vector<int> get_numbers() const;

        void sort();
};

#endif
