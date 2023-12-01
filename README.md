# arc-01-my_mastermind
<div class="card-block">
<div class="row">
<div class="col tab-content">
<div class="tab-pane active show" id="subject" role="tabpanel">
<div class="row">
<div class="col-md-12 col-xl-12">
<div class="markdown-body">
<p class="text-muted m-b-15">
</p><h1>My Mastermind</h1>
<p>Remember to git add &amp;&amp; git commit &amp;&amp; git push each exercise!</p>
<p>We will execute your function with our test(s), please DO NOT PROVIDE ANY TEST(S) in your file</p>
<p>For each exercise, you will have to create a folder and in this folder, you will have additional files that contain your work. Folder names are provided at the beginning of each exercise under <code>submit directory</code> and specific file names for each exercise are also provided at the beginning of each exercise under <code>submit file(s)</code>.</p>
<hr>
<table>
<thead>
<tr>
<th>My Mastermind</th>
<th></th>
</tr>
</thead>
<tbody>
<tr>
<td>Submit directory</td>
<td>.</td>
</tr>
<tr>
<td>Submit files</td>
<td>Makefile - *.c - *.h</td>
</tr>
</tbody>
</table>
<h3>Description</h3>
<h3>SPECIFICATIONS</h3>
<p>Write a program called mastermind; it will be an implementation of the famous game.</p>
<h3>NAME</h3>
<p>my_mastermind</p>
<h3>SYNOPSIS</h3>
<p>my_mastermind [-ct]</p>
<h3>DESCRIPTION</h3>
<p>Mastermind is a game composed of 9 pieces of different colors.
A secret code is then composed of 4 distinct pieces.</p>
<p>The player has 10 attempts to find the secret code.
After each input, the game indicates to the player the number of well placed pieces and the number of misplaced pieces.</p>
<p>Pieces will be '0' '1' '2' '3' '4' '5' '6' '7' '8'.</p>
<p>If the player finds the code, he wins, and the game stops.
A misplaced piece is a piece that is present in the secret code butthat is not in a good position.</p>
<p>You must read the player's input from the standard input.</p>
<p>Your program will also receive the following parameters:
-c [CODE]: specifies the secret code. If no code is specified, a random code will be generated.
-t [ATTEMPTS]: specifies the number of attempts; by default, the playerhas 10 attempts.</p>
<p><strong>Example 00</strong></p>
<pre class=" language-plain"><code class=" language-plain">PROMPT&gt;./my_mastermind -c "0123"
Will you find the secret code?
Please enter a valid guess
---
Round 0
&gt;1456
Well placed pieces: 0
Misplaced pieces: 1
---
Round 1
&gt;tata
Wrong input!
&gt;4132
Well placed pieces: 1
Misplaced pieces: 2
---
Round 2
&gt;0123
Congratz! You did it!
</code></pre>
<h3>Technical information</h3>
<ol>
<li>
<p>you must create a Makefile, and the ouput is the command itself
It will contain rule all/clean/fclean (re =&gt; fclean + all)</p>
</li>
<li>
<p>You can use:</p>
</li>
</ol>
<ul>
<li>printf(3)</li>
<li>write(2)</li>
<li>read(2)</li>
<li>rand() (/ srand())</li>
<li>time()</li>
<li>atoi()</li>
<li>strcmp()</li>
</ul>
<ol start="3">
<li>You can NOT use:</li>
</ol>
<ul>
<li>Any functions/syscalls which does not appear in the previous list</li>
<li>Yes, it includes <strong>exit</strong>
</li>
</ul>
<ol start="4">
<li>
<p>Consider writing a README.md to describe your project and how it works.</p>
</li>
<li>
<p>Your mastermind needs to handle the sequence <code>Ctrl + d</code>. It's End Of File.
It's consider as a normal execution.</p>
</li>
<li>
<p>read() is a syscall difficult to apprehend, you will have time to deal more with it in a later project. In this project, you should read 1 character by 1 (use read(0, &amp;c, 1)) and add them one by one to a buffer until you encounter a newline.</p>
</li>
</ol>
<p>Example:</p>
<pre class=" language-plain"><code class=" language-plain">[/tmp/]bash
bash-3.2$ exit
[/tmp/]
</code></pre>
<p>In this example, bash exited successfully and also printed "exit".</p>
<h3>Output formats</h3>
<ol>
<li>When your program starts, you must display:</li>
</ol>
<pre class=" language-plain"><code class=" language-plain">Will you find the secret code?
Please enter a valid guess
</code></pre>
<ol start="2">
<li>When the user wins, you must display:</li>
</ol>
<pre class=" language-plain"><code class=" language-plain">Congratz! You did it!
</code></pre>
<ol start="3">
<li>When the user enters an invalid code, you must respect the following format:</li>
</ol>
<pre class=" language-plain"><code class=" language-plain">Well placed pieces: X
Misplaced pieces: Y
</code></pre>
<p>X and Y are two digits with the correct values.</p>
<h3>Requirements</h3>
<ul>
<li>Your code must be compiled with the flags <strong>-Wall -Wextra -Werror</strong>.</li>
<li>Multiline macros are forbidden</li>
<li>You should have multiple file .c but it's forbidden to include them (#include another_file.c) use your Makefile to compile them together.</li>
<li>Macros with logic (while/if/variables/...) are forbidden</li>
</ul>
<h3>Advanced Testing</h3>
<p>Gandalf tests using a synthax similar to this one:</p>
<pre class=" language-plain"><code class=" language-plain">echo "1234
2345
3456" | ./my_mastermind -c 3456
</code></pre>
<p>It will hightlight that you are not using read() well.</p>
<h3>Hint(s)</h3>
<ul>
<li>man 2 read</li>
<li>man rand</li>
</ul>
<p><strong>M</strong>akefile, case sensitivity is important.</p>

<p></p>
</div>

</div>
</div>
</div>
<div class="tab-pane" id="resources" role="tabpanel">
</div>
</div>
</div>
</div>
