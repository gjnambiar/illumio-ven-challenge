# illumio-ven-challenge
This was a fun coding challenge which I enjoyed working on.
I didn't have much time to create any intensive testing scripts, so I used the example inputs given in 
randomized orders to test, slightly modifying so certain addresses had a translation. 
I chose to use maps has the key-value realtion meant being able to pull up the translation easily once, 
the original address and the flow were matched. Also maps in C++ uses a simple ordering which sped up the search
process and seprarated the addresses with "*" and those without. 
As of now the run time would be O(MN). If I had more time I woulf try to reach an effiency of O(N), if possible.
For this cahhlenge I made the assumption that the ip adress and the port will either be a valid numeric sequence 
or a "*". I did not code for an ip value like "2.\*.3.4.5". I also made sure that if a numeric squence was available 
the translation would follow that original address, rather than one with a "*".
