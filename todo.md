# String Lookup Bug #
If multiple enum entries have the same value.
The string for the entry which is returned by ToString will be the first encountered.

# Map #
If we let an enum map to a generic type, we can't use default stringification.


```c
// map enum to strings
ENUM_MAP(Integers, char*);
_(ZERO) => ZERO, | {(ZERO), #ZERO, NULL}
_V(TWO, 2) => TWO = 2, | {(TWO), #TWO, NULL}
_D(TWO, "Two") => TWO, | {(TWO), "Two", NULL}
_VD(TWO, 2, "Two") => TWO = 2, | {(TWO), "Two", NULL}

ENUM_MAP(Floats, float);

_D(THREE, 3.0f) => THREE, | {(THREE), #THREE, 3.0f}
_VD(THREE, 3, 3.0f) => THREE = 3, | {(THREE), #THREE, 3.0f}
_SD(THREE, "Three", 3.0f) => THREE, | {(THREE), "Three", 3.0f}
_VSD(THREE, 3, "Three", 3.0f) => THREE = 3, | {(THREE), "Three", 3.0f}
_SD(PI, "Pi", 3.14159f) => PI, | {(PI), "Pi", 3.14159f} // Dangerous!!! PI == 4 !

// Can't assume data is char* and stringify it.

// map enum to floats
_(ZERO) => ZERO, | {(ZERO), #ZERO}
_V(TWO, 2) => TWO = 2, | {(TWO), #TWO} // void * strings interpreted as floats!
_D(TWO, 2.0f, "Two point zero")
_DS(PI, 3.1416f, "Pi")
```

Let engineers implement register tables and properties using manual Applied X-Macro techniques.

Provide this only for Enum/String mapping.

To use `void*` we must provide a separate interface never has to do default stringification.


# Monotonic #
`For all (x, y) s.t. x <= y, [x] <= [y]`

`enum_monotonic.h`

If we can restrict to monotonic only we can do binsearch instead of linear.

Probably only of benefit for really large lists though.

Apart from suffering from the string lookup bug


# Increasing #
`For all (x, y) s.t. x <= y, [x] < [y]`


# Contiguous #
`For all x, [x]+1 = [x+1]`

`enum_contiguous.h`

Provide a separate interface for enums which can be accessed O(1) instead of O(n)?

```c
#define AS_ENUM(name) name,

ENUM_STRICT(e)
    enum e { \
        e(AS_ENUM) \
    } \

#define ENUM_AS_NAME(name)       {#name},

#define ENUM_IMPL(e) \
    static const struct e##_PropertiesEntry\
    {\
        char const* name;\
    } e##_IMPL[] = \
    { \
        e(ENUM_AS_NAME) \
    }

#define ENUM_DEFINE_TOSTRING(e, fname) \
    ENUM_DECLARE_TOSTRING(e, fname) \
    { \
        if ((literal) < 0 \
            || (literal) >= sizeof(e##_IMPL)/sizeof(*e##_IMPL)) \
        { \
            return "ERROR: UNKNOWN ENUM TYPE"; \
        } \
        return e##_IMPL[idx].name; \
    } \
```

