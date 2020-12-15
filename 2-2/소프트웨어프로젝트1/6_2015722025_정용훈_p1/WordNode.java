package p1;
import p1.Pair;

public class WordNode {
   
   private Pair<String,String> wordmean=new Pair<String,String>();   //wordmean Pair   
   private WordNode pLeft=null;               // BST Left Pointer
   private WordNode pRight=null;            // BST Right Pointer
   private WordNode pNext=null;               // Queue Next Pointer
   
   WordNode()
   {
   }
   
   public void DeletePair(WordNode node) // delete pair
   {
      node.wordmean=null; // set wordmean node to null
   }
   public String GetWord() // get word
   {
      return wordmean.first; // return word
   }
   public String GetMean() // get mean
   {
      return wordmean.second; // return mean
   }
   public WordNode GetLeft() // get left
   {
      return pLeft; // return left
   }
   public WordNode GetRight() // get right
   { 
      return pRight; // return right
   }
   public WordNode GetNext() // get next
   {
      return pNext; // return next
   }
   public void   SetWord(String word) // set word
   {
      wordmean.first=word; // set word
   }
   public void SetMean(String mean) // set mean
   {
      wordmean.second=mean; // set mean
   }
   public void   SetLeft(WordNode node) // set left
   {
      pLeft=node; // set node to left
   }
   public void   SetRight(WordNode node) // set right 
   {
      pRight=node; // set node to right
   } 
   public void   SetNext(WordNode node) // set next
   {
      pNext=node; // set node to next
   }   
   
}