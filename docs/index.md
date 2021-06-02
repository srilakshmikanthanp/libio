# libio Docs

~~~c
type read(type, FILE* fileptr, const char* format)
~~~

This functions try to read type from fileptr if sucess then returns value of type els MAX of type or MIN of type.

**Paramaters**

```
type    - type to read
fileptr - from file
format  - prints and ask input may be NULL
```

**Return**

```
On success the value is returned if fails the MAX or MIN of type is returned
```

---

~~~c
type input(type, const char* format)
~~~

This functions try to read type from stdin if sucess then returns value of type els MAX of type or MIN of type.

**Paramaters**

```
type    - type to read
format  - prints and ask input may be NULL
```

**Return**

```
On success the value is returned if fails the MAX or MIN of type is returned
```

---

~~~c
int write(FILE* fileptr, ...)
~~~

```
This function prints the strings to file and return printed count
```

**Parameters**

```
fileptr - from file
...     - varadic const char* 's
```

**Return**

```
number of arguments printed
```

---

~~~c
int print(...)
~~~

```
This function prints the strings to file and return printed count
```

**Parameters**

```
...     - varadic const char* 's
```

**Return**

```
number of arguments printed
```

---

~~~c
string str(type value)
~~~

```
This function converts value to string and returns it
```

**Parametrs**

```
value  - value to convert
```

**Return**

```
returns the string or NULL if fails
```

_This is not same prototype that implemented, this is only for understanding_
