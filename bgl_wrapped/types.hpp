#include <iostream>

#pragma once

enum class VertexType {
    Image,
    Scalar,
    Node,
    None
};

enum class ParseVertexTask {
   Computation, 
   Buffer,
   None
};

ParseVertexTask set_task(VertexType type) {
    switch (type) {
        case VertexType::Image:
        case VertexType::Scalar:
            return ParseVertexTask::Buffer;
        case VertexType::Node:
            return ParseVertexTask::Computation;
        default: 
            return ParseVertexTask::None;
    }
}

class VertexTypeBase
{
    public:
        std::string name;
        ParseVertexTask task;
        VertexType type;

    public:
        VertexTypeBase() : name(""), task(ParseVertexTask::None) {
            task = set_task(type);
        };

        VertexTypeBase(std::string _name) : name(_name), task(ParseVertexTask::None) {
            task = set_task(type);
        };

        VertexTypeBase(VertexType _type) : name(""), type(_type) {
            task = set_task(type);
        };

        VertexTypeBase(std::string _name, VertexType _type) : name(_name), type(_type) {
            task = set_task(type);
        };

        virtual ~VertexTypeBase() = default;


        VertexType get_type() { return type; };

        ParseVertexTask get_task() { return task; };

        std::string get_name() { return name; };

        void set_name(std::string _name) { name = _name; };
};

class Image: public VertexTypeBase
{
    public:
        Image() : VertexTypeBase(VertexType::Image) { };

        Image(std::string _name) : VertexTypeBase(_name, VertexType::Image) { };

        virtual ~Image() = default;
};

class Scalar: public VertexTypeBase
{
    public:
        Scalar() : VertexTypeBase(VertexType::Scalar) { };

        Scalar(std::string _name) : VertexTypeBase(_name, VertexType::Scalar) { };

        virtual ~Scalar() = default;
};

class Node: public VertexTypeBase
{
    public:
        Node() : VertexTypeBase(VertexType::Node) { };

        Node(std::string _name) : VertexTypeBase(_name, VertexType::Node) { };

        virtual ~Node() = default;
};
