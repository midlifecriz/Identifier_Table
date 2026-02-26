#include <iostream>
#include <string.h>
#include "variable_descriptor.hpp"
#include "vector_descriptor.hpp"
#include "matrix_descriptor.hpp"
#include "input.hpp"
#include "descriptor.hpp"
#include "identifier.hpp"
#include "table.hpp"
#include <gtest/gtest.h>


//VARIABLE DESCRIPTOR
TEST(VariableDescriptorTest, ConstructorTest) {
    VariableDescriptor<int> var1;
    EXPECT_EQ(false, var1.init());

    VariableDescriptor<int> var2(100);
    EXPECT_EQ(100, var2.value());
    EXPECT_EQ(true, var2.init());
}


TEST(VariableDescriptorTest, GetValueTest) {
    VariableDescriptor<int> var(10);
    EXPECT_EQ(10, var.value());
}


TEST(VariableDescriptorTest, GetInitializedTest) {
    VariableDescriptor<int> var1;
    VariableDescriptor<int> var2(-1);
    EXPECT_EQ(false, var1.init());
    EXPECT_EQ(true, var2.init());
}


TEST(VariableDescriptorTest, CopyOperatorTest) {
    VariableDescriptor<int> var;
    var = 1;
    EXPECT_EQ(1, var.value());
    EXPECT_EQ(true, var.init());

    VariableDescriptor<int> var1;
    VariableDescriptor<int> var2(100);
    var1 = var2;
    EXPECT_EQ(100, var1.value());
    EXPECT_EQ(true, var1.init());
}


//VECTOR DESCRIPTOR
TEST(VectorDescriptorTest, ConstructorTest) {
    VectorDescriptor<int> vector;
    EXPECT_EQ(0, vector.size());
    EXPECT_EQ(1, vector.capacity());
}


TEST(VectorDescriptorTest, CopyOperatorTest) {
    VectorDescriptor<VariableDescriptor<int>> vec1;
    VariableDescriptor<int> v1(1), v2(10);
    vec1.insert(v1, 0);
    vec1.insert(v1, 1);

    VectorDescriptor<VariableDescriptor<int>> vec2;
    vec2 = vec1;
    EXPECT_EQ(vec2.size(), vec1.size());
    EXPECT_EQ(vec2.capacity(), vec1.capacity());
}


TEST(VectorDescriptorTest, GetInitTest) {
    VectorDescriptor<VariableDescriptor<int>> vec1;
    VectorDescriptor<VariableDescriptor<int>> vec2;
    VariableDescriptor<int> var(1);
    vec2.insert(var, 0);

    EXPECT_EQ(false, vec1.init());
    EXPECT_EQ(true, vec2.init());
}


TEST(VectorDescriptorTest, SizeAndCapacityTest) {
    VectorDescriptor<VariableDescriptor<int>> vec;
    EXPECT_EQ(0, vec.size());
    EXPECT_EQ(1, vec.capacity());
    VariableDescriptor<int> var1, var2, var3;
    vec.insert(var1, 0);
    EXPECT_EQ(1, vec.size());
    EXPECT_EQ(1, vec.capacity());
    vec.insert(var2, 1);
    EXPECT_EQ(2, vec.size());
    EXPECT_EQ(2, vec.capacity());
    vec.insert(var3, 2);
    EXPECT_EQ(3, vec.size());
    EXPECT_EQ(4, vec.capacity());
}


TEST(VectorDescriptorTest, InsertTest) {
    VectorDescriptor<int> vec;
    int v1 = 1;
    int v2 = 2;
    int v3 = 3;
    int v4 = 150;

    vec.insert(v1, 0);
    EXPECT_EQ(vec[0], v1);
    EXPECT_EQ(vec.size(), 1);

    vec.insert(v2, 1);
    EXPECT_EQ(vec[1], v2);
    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec.capacity(), 2);

    vec.insert(v3, 0);
    EXPECT_EQ(vec[0], v3);
    EXPECT_EQ(vec[1], v1);
    EXPECT_EQ(vec[2], v2);
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec.capacity(), 4);

    EXPECT_THROW(
        try {
            vec.insert(v4, 5);
        }
        catch (const std::exception& err) {
            EXPECT_STREQ("INDEX OUT OF RANGE", err.what());
            throw;
        }, std::exception);
}


TEST(VectorDescriptorTest, EraseTest) {
    VectorDescriptor<int> vec;
    int v1 = 1;
    int v2 = 2;
    int v3 = 3;
    int v4 = 4;
    vec.insert(v1, 0);
    vec.insert(v2, 1);
    vec.insert(v3, 2);
    vec.insert(v4, 3);

    vec.erase(3);
    EXPECT_EQ(vec.size(), 3);

    vec.erase(1);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 3);
    EXPECT_EQ(vec.size(), 2);

    EXPECT_THROW(
        try {
            vec.erase(6);
        }
        catch (const std::exception& err) {
            EXPECT_STREQ("INDEX OUT OF RANGE", err.what());
            throw;
        }, std::exception);
}


//MATRIX DESCRIPTOR
TEST(MatrixDescriptorTest, ConstructorTest) {
    MatrixDescriptor<int> m;
    EXPECT_EQ(1, m.height());
    EXPECT_EQ(1, m.width());
}


TEST(MatrixDescriptorTest, CopyOperatorTest) {
    MatrixDescriptor<int> m1;
    MatrixDescriptor<int> m2;
    EXPECT_EQ(m1.width(), m2.width());
    EXPECT_EQ(m2.height(), m2.height());
}


//IDENTIFIER
TEST(IdentifierTest, ConstructorTest) {
    Identifier id1;
    std::string name("name");
    std::string n("nnnnnnnnnnnname");
    Identifier id2(name);

    EXPECT_EQ("noname", id1.get_name());
    EXPECT_EQ("name", id2.get_name());
    EXPECT_EQ(nullptr, id1.get_descriptor());
    EXPECT_EQ(nullptr, id2.get_descriptor());
    
    EXPECT_THROW(
        try {
            Identifier id3(n);
        }
        catch (const std::exception& err) {
            EXPECT_STREQ("NAME IS TOO LONG", err.what());
            throw;
        }, std::exception);
}


TEST(IdentifierTest, SettersTest) {
    Identifier id;
    std::string n1("name");
    std::string n2("nnnnnnnnnnnnnnnnnname");
    std::string n3("ыбыб");
    VariableDescriptor<int> v1, v2;
    Descriptor* ptr1 = static_cast<Descriptor*>(&v1);
    Descriptor* ptr2 = static_cast<Descriptor*>(&v2);

    id.set_name(n1);
    EXPECT_EQ(id.get_name(), n1);

    id.set_descriptor(ptr1);
    EXPECT_EQ(id.get_descriptor(), ptr1);

    EXPECT_THROW(
        try {
            id.set_name(n2);
        }
        catch (const std::exception& err){
            EXPECT_STREQ("NAME IS TOO LONG", err.what());
            throw;
        }, std::exception);
    
    id.set_parameters(n3, ptr2);
    EXPECT_EQ(id.get_name(), n3);
    EXPECT_EQ(id.get_descriptor(), ptr2);

    EXPECT_THROW(
            try {
                id.set_parameters(n2, ptr1);
            }
            catch (const std::exception& err) {
                EXPECT_STREQ("NAME IS TOO LONG", err.what());
                throw;
            }, std::exception);
}


TEST(IdentifierTest, CompareOperatorsTest) {
    std::string n1("ayaya");
    std::string n2("bebeb");
    Identifier id1(n1);
    Identifier id2(n2);

    EXPECT_EQ(true, id2 > id1);
    EXPECT_EQ(false, id1 > id2);
    EXPECT_EQ(false, id1 == id2);

    id2.set_name(n1);
    EXPECT_EQ(false, id2 > id1);
    EXPECT_EQ(false, id1 > id2);
    EXPECT_EQ(true, id1 == id2);
}


TEST(IdentifierTest, CopyOperatorTest) {
    std::string name("ыбыб");
    Identifier id1(name);
    Identifier id2;
    id2 = id1;
    EXPECT_EQ(true, id1 == id2);
}


//TABLE
TEST(TableTest, ConstructorTest) {
    Table<int> t;
    EXPECT_EQ(0, t.size());

    Table<int> t1(t);
    EXPECT_EQ(t.size(), t1.size());
}


TEST(TableTest, InsertTest) {
    Table<Identifier> table;
    std::string n1("a");
    std::string n2("b");
    Identifier id1(n1);
    Identifier id2(n2);
    Identifier id3;
    id3 = id1;
    table.insert(id1);
    table.insert(id2);

    EXPECT_THROW({
        try {
            table.insert(id3);
        }
        catch (const std::exception& err) {
            EXPECT_STREQ("DUPLICATE", err.what());
            throw;
        }
    }, std::exception);
}


TEST(TableTest, ClearTest) {
    Table<Identifier> table;
    std::string n1("a");
    std::string n2("b");
    std::string n3("c");
    std::string n4("d");

    Identifier id1(n1);
    Identifier id2(n2);
    Identifier id3(n3);
    Identifier id4(n4);

    Table<Identifier>::Iterator it;
    Table<Identifier>::Iterator start;
    Table<Identifier>::Iterator end;

    table.insert(id1);
    table.insert(id2);
    table.insert(id3);
    table.insert(id4);

    table.clear();
    EXPECT_EQ(0, table.size());
}


TEST(TableTest, EraseTest) {
    Table<Identifier> table;
    std::string n1("a");
    std::string n2("b");
    std::string n3("c");
    std::string n4("d");

    Identifier id1(n1);
    Identifier id2(n2);
    Identifier id3(n3);
    Identifier id4(n4);

    Table<Identifier>::Iterator it;
    Table<Identifier>::Iterator start;
    Table<Identifier>::Iterator end;

    table.insert(id1);
    table.insert(id2);
    table.insert(id3);
    table.insert(id4);

    it = table.find(id1);
    table.erase(it);
    EXPECT_EQ(3, table.size());
}


TEST(TableTest, EraseRangeTest) {
    Table<Identifier> table;
    std::string n1("a");
    std::string n2("b");
    std::string n3("c");
    std::string n4("d");

    Identifier id1(n1);
    Identifier id2(n2);
    Identifier id3(n3);
    Identifier id4(n4);

    Table<Identifier>::Iterator it;
    Table<Identifier>::Iterator start;
    Table<Identifier>::Iterator end;

    table.insert(id1);
    table.insert(id2);
    table.insert(id3);
    table.insert(id4);

    start = table.find(id2);
    end = table.find(id4);
    table.erase(start, end);
    EXPECT_EQ(2, table.size());
}


TEST(TableTest, FindTest) {
    Table<int> table;
    int a = 1; //b = 100;
    table.insert(a);
    Table<int>::Iterator it = table.find(a);
    EXPECT_EQ(*it, 1);

    /*
    EXPECT_THROW({
        try {
            table.find(b);
        }
        catch (const std::exception& err) {
            EXPECT_STREQ("ELEMENT WAS NOT FOUND", err.what());
            throw;
        }
    }, std::exception);
    */
}


//VECTOR
TEST(VectorTest, ConstructorTest) {
    Vector<int> vector;
    EXPECT_EQ(0, vector.size());
    EXPECT_EQ(1, vector.capacity());
}


TEST(VectorTest, CopyOperatorTest) {
    Vector<int> vec1;
    int v1 = 1, v2 = 10;
    vec1.insert(v1, 0);
    vec1.insert(v2, 1);

    Vector<int> vec2;
    vec2 = vec1;
    EXPECT_EQ(vec1[0], vec2[0]);
    EXPECT_EQ(vec1[1], vec2[1]);
    EXPECT_EQ(vec2.size(), vec1.size());
    EXPECT_EQ(vec2.capacity(), vec1.capacity());
}


TEST(VectorTest, FullEmptyTest) {
    Vector<int> vec1;
    Vector<int> vec2;
    int var = 1;;
    vec2.insert(var, 0);

    EXPECT_EQ(false, vec2.empty());
    EXPECT_EQ(true, vec1.empty());
    EXPECT_EQ(false, vec1.full());
    EXPECT_EQ(true, vec2.full());
}


TEST(VectorTest, SizeAndCapacityTest) {
    Vector<VariableDescriptor<int>> vec;
    EXPECT_EQ(0, vec.size());
    EXPECT_EQ(1, vec.capacity());
    VariableDescriptor<int> var1, var2, var3;
    vec.insert(var1, 0);
    EXPECT_EQ(1, vec.size());
    EXPECT_EQ(1, vec.capacity());
    vec.insert(var2, 1);
    EXPECT_EQ(2, vec.size());
    EXPECT_EQ(2, vec.capacity());
    vec.insert(var3, 2);
    EXPECT_EQ(3, vec.size());
    EXPECT_EQ(4, vec.capacity());
}


TEST(VectorTest, InsertTest) {
    Vector<int> vec;
    int v1 = 1;
    int v2 = 2;
    int v3 = 3;
    int v4 = 150;

    vec.insert(v1, 0);
    EXPECT_EQ(vec[0], v1);
    EXPECT_EQ(vec.size(), 1);

    vec.insert(v2, 1);
    EXPECT_EQ(vec[1], v2);
    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec.capacity(), 2);

    vec.insert(v3, 0);
    EXPECT_EQ(vec[0], v3);
    EXPECT_EQ(vec[1], v1);
    EXPECT_EQ(vec[2], v2);
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec.capacity(), 4);

    EXPECT_THROW(
        try {
            vec.insert(v4, 5);
        }
        catch (const std::exception& err) {
            EXPECT_STREQ("INDEX OUT OF RANGE", err.what());
            throw;
        }, std::exception);
}


TEST(VectorTest, EraseTest) {
    Vector<int> vec;
    int v1 = 1;
    int v2 = 2;
    int v3 = 3;
    int v4 = 4;
    vec.insert(v1, 0);
    vec.insert(v2, 1);
    vec.insert(v3, 2);
    vec.insert(v4, 3);

    vec.erase(3);
    EXPECT_EQ(vec.size(), 3);

    vec.erase(1);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 3);
    EXPECT_EQ(vec.size(), 2);

    EXPECT_THROW(
        try {
            vec.erase(6);
        }
        catch (const std::exception& err) {
            EXPECT_STREQ("INDEX OUT OF RANGE", err.what());
            throw;
        }, std::exception);
}


int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}

