
<h1>Welcome to my Mastermind</h1>

<h2>Task</h2>
<p>The task is to implement a simple Mastermind game in C. The game generates a secret code, and the player must guess the code within a limited number of attempts.</p>

<h2>Description</h2>
<p>This C program implements a simple Mastermind game where the player has to guess a secret code. The secret code can either be randomly generated or provided as a command-line argument. The player has a limited number of attempts to guess the code correctly. After each guess, the program provides feedback on the number of correctly placed digits and the number of misplaced digits. The game continues until the player correctly guesses the code or exhausts all attempts.</p>

<h2>Installation</h2>
<p>To compile the program, make sure you have a C compiler (e.g., gcc) installed on your system. Then follow these steps:</p>
<ol>
    <li>Clone or download the repository to your local machine.</li>
    <li>Open a terminal and navigate to the directory containing the source code files.</li>
    <li>Run the <code>make</code> command to compile the program.</li>
    <li>After successful compilation, you will find an executable named <code>game</code> in the same directory.</li>
</ol>

<h2>Usage</h2>
<p>Once the program is compiled, you can run it from the terminal. The program accepts the following command-line arguments:</p>
<ul>
    <li><code>-c &lt;code&gt;</code>: Provide the secret code manually. <code>&lt;code&gt;</code> should be a 4-digit number with no repeating digits.</li>
    <li><code>-t &lt;max_rounds&gt;</code>: Set the maximum number of rounds (attempts) for the game. The default value is 10.</li>
</ul>
<p>If no command-line arguments are provided, the program generates a random secret code and uses the default maximum rounds value.</p>
<p>To run the program with command-line arguments:</p>
<pre>./game -c &lt;code&gt; -t &lt;max_rounds&gt;</pre>
<p>Example:</p>
<pre>./game -c 1234 -t 15</pre>
<p>Follow the on-screen instructions to play the game. Enter your guesses when prompted and press Enter.</p>
