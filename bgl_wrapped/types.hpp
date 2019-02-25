#include <iostream>

#pragma once

enum class ParseVertexType {
    None,
    Image,
    Scalar,
    Node
};

enum class ParseVertexTask {
   None,
   Computation, 
   Buffer
};

ParseVertexTask set_task(ParseVertexType type) {
    switch (type) {
        case ParseVertexType::Image:
        case ParseVertexType::Scalar:
            return ParseVertexTask::Buffer;
        case ParseVertexType::Node:
            return ParseVertexTask::Computation;
        default: 
            return ParseVertexTask::None;
    }
}

class ParseVertexTypeBase
{
    public:
        std::string name;
        ParseVertexTask task;
        ParseVertexType type;

        ParseVertexTypeBase() : name(""), task(ParseVertexTask::None) { 
            task = set_task(type);
        };

        ParseVertexTypeBase(std::string _name) : name(_name), task(ParseVertexTask::None) { 
            task = set_task(type);
        };

        ParseVertexTypeBase(ParseVertexType _type) : name(""), type(_type) {
            task = set_task(type);
        };

        ParseVertexTypeBase(std::string _name, ParseVertexType _type) : name(_name), type(_type) {
            task = set_task(type);
        };

        virtual ~ParseVertexTypeBase() = default;


        ParseVertexType get_type() { return type; };

        ParseVertexTask get_task() { return task; };

        std::string get_name() { return name; };

        void set_name(std::string _name) { name = _name; };
};

class Image: public ParseVertexTypeBase
{
    public:
        Image() : ParseVertexTypeBase(ParseVertexType::Image) { };

        Image(std::string _name) : ParseVertexTypeBase(_name, ParseVertexType::Image) { };

        virtual ~Image() = default;
};

class Scalar: public ParseVertexTypeBase
{
    public:
        Scalar() : ParseVertexTypeBase(ParseVertexType::Scalar) { };

        Scalar(std::string _name) : ParseVertexTypeBase(_name, ParseVertexType::Scalar) { };

        virtual ~Scalar() = default;
};

class Node: public ParseVertexTypeBase
{
    public:
        Node() : ParseVertexTypeBase(ParseVertexType::Node) { };

        Node(std::string _name) : ParseVertexTypeBase(_name, ParseVertexType::Node) { };

        virtual ~Node() = default;
};
