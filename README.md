# minishell
**_rewriting a simple shell_**

This project is an attempt ti recode our own little bash. A program capable of parsing a prompt and launching executables with arguments, along with a few built-in functions.

<p align="center">
  <img src="imagepath.png is here" width="100%" />
</p>


### Usage

``make`` will create the ``minishell`` executable.

Simply run it with :

```
./minishell
```

### Options:

* Minishell runs executables from an absolute, relative or environment PATH (``/bin/ls`` or ``ls``), including arguments or options. ``'`` and ``"`` work the same as bash, except for multiline commands.

* You can separate commands with ``;``, as well as use redirections ``>`` ``>>`` ``<`` and pipes ``|``.

* Environment variables are handled, like ``$HOME``, including the return code ``$?``, or adding any commands/paths as an environmentale variable and using them in your commands afterwards

* you can use ``Ctrl-C`` to interrupt and ``Ctrl-\`` to quit a program, as well as ``Ctrl-D`` to throw an EOF, same as in bash.

* Some functions are "built-in", meaning we don't call the executable, they are re-coded  directly. It's the case for ``echo``, ``pwd``, ``cd``, ``env``, ``export``, ``unset`` and ``exit``.


### Credits

This is a team project, which was done with @[DenKrylov](https://github.com/DenKrylov).

I was responsible for the execution, built-in functions, signal handling and pipes and error checks and messages.

@[DenKrylov](https://github.com/DenKrylov) did the parsing and redirections part.
