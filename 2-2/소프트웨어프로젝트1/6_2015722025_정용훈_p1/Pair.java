package p1;

public class Pair<F,S> { // Pair class
    public F first=null; // location of word 
    public S second=null; // location of meaning

    public Pair(F first, S second) // constructor overloading
    {
      this.first = first; // saving word
      this.second = second; // saving meaning
    }
    public Pair() // constructor
    {
        this.first = null;
        this.second = null;
    }

    static <F,S> Pair<F,S> of(F first, S second) // static pair function
    {
        return new Pair<F,S>(first, second);
    }
  }