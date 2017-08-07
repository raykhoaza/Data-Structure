// $Id: jxref.java,v 1.18 2014-05-13 01:27:24-07 - - $
//NAME: KHOA LUONG USERNAME: KLUON7@UCSC.EDU
import java.io.*;
import java.util.Scanner;
import static java.lang.System.*;
import java.util.*;

class jxref {
   static boolean debug = false;
   static boolean lowercase = false;
   static final String STDIN_NAME = "-";

   static class printer implements visitor <String, queue <Integer>> {
      public void visit (String key, queue <Integer> value) {
         System.out.printf ("%s %s", key, value);
         for (int linenr: value) out.printf (" %d", linenr);
         System.out.printf ("%n");
      }
   }
  
   static void options(String option){
      if(option.contains("d")) {debug = true;}
      if(option.contains("f")) {lowercase = true;}
   }

   static void xref_file (String filename, Scanner scan) {
      treemap <String, queue <Integer>> map =
      new treemap <String, queue <Integer>> ();
      queue<Integer> numberqueue = new queue<Integer>();
      for (int linenr = 1; scan.hasNextLine (); ++linenr){
         for (String word: scan.nextLine().split ("\\W+")) {
            if (word.matches ("^\\d*$")) continue;
            if (lowercase){
               word = word.toLowerCase();
            }
            numberqueue = map.get(word);
            if (numberqueue!=null){
               numberqueue.insert(linenr);
            }
            else { 
               numberqueue = new queue<Integer>();
               map.put(word, numberqueue);
               numberqueue.insert(linenr);
            }
         }
      }
      if(debug){
         map.debug_dump();
         return;
      }
      visitor <String, queue <Integer>> print_fn = new printer ();
      map.do_visit (print_fn);
   }

   public static void main (String[] args) {
      if (args[0].charAt(0)=='-'){options(args[0]);}
      if(args.length == 0) {
         xref_file (STDIN_NAME, new Scanner (in));
      }else {
         for (int argi = 0; argi < args.length; ++argi) {
            String filename = args[argi];
            if (filename.equals (STDIN_NAME)) {
               xref_file (STDIN_NAME, new Scanner (in));
            }else {
               try {
                  Scanner scan = new Scanner (new File (filename));
                  System.out.println();
                  System.out.println(":::::::::::::::::::::::::::::"
                  +"::::::::::::::::::::::::::::::::::::");
                  System.out.println(filename);
                  System.out.println(":::::::::::::::::::::::::::::"
                  +"::::::::::::::::::::::::::::::::::::");
                  System.out.println();
                  xref_file (filename, scan);
                  scan.close ();
               }catch (IOException error) {
                  auxlib.warn (error.getMessage ());
               }
            } 
         }
      }
      auxlib.exit ();
   }
}

