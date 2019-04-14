//
// Created by Furkat MALLABAEV on 2019-04-13.
//

#ifndef EXPERT_SYSTEM_FACT_HPP
#define EXPERT_SYSTEM_FACT_HPP

class Fact {
   public:
    Fact(char c) : _label(c), _is_fact(false), _status(false), _initial(false)
    {
    }

    Fact(const Fact &) = default;
    Fact(Fact &&) = default;
    Fact &operator=(const Fact &) = default;
    Fact &operator=(Fact &&) = default;

    void setInitial()
    {
        _initial = true;
    }

    bool isInitial() const
    {
        return _initial;
    }

    char getLabel() const
    {
        return _label;
    }

    void setStatus()
    {
        _status = true;
    }

    bool getStatus() const
    {
        return _status;
    }

    Fact &operator=(bool b)
    {
        _is_fact = b;
        return *this;
    }

    bool operator==(char c) const
    {
        return _label == c;
    }

    bool operator==(const Fact &f) const
    {
        return _label == f._label;
    }

    operator bool() const
    {
        return _is_fact;
    }

   private:
    char _label;
    bool _is_fact;
    bool _status;
    bool _initial;
};

bool operator==(char c, const Fact &f);

#endif  // EXPERT_SYSTEM_FACT_HPP
