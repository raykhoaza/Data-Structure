// $Id: edfile.java,v 1.62 2014-04-28 23:49:39-07 - - $
// USER: KHOA LUONG USERNAME: kluon7
import java.io.*;
import java.util.Scanner;
import static java.lang.System.*;

class edfile{
   public static int linesread = 0;
   public static int lineswritten = 0;

   public static void writefile(dllist lines, String filename){
      PrintWriter outfile = null;
      String newfile = filename;
      try {
         outfile = new PrintWriter(newfile);
      }
      catch (FileNotFoundException error) {
         auxlib.exit_status = auxlib.EXIT_FAILURE;
         auxlib.exit();
      }
      lines.setposition(dllist.position.FIRST);
      while(!lines.isEnd()){
         lines.printline();
         lines.setposition(dllist.position.FOLLOWING);
         lineswritten ++;
      }
      lines.printline();
      lineswritten ++;
      System.out.printf("%d lines written.\n", lineswritten);
      outfile.close();
   
   }

   public static void readfile(dllist lines, String filename){
      try{
      Scanner file = new Scanner (new File (filename));
         while (file.hasNextLine()){
            String line = file.nextLine();
            lines.insert(line, dllist.position.FOLLOWING);
            linesread ++;
         }
      }
      catch (FileNotFoundException error){
         auxlib.exit_status = auxlib.EXIT_FAILURE;
         auxlib.exit();
      }

   }

   public static void main (String[] args) {
      boolean want_echo = false;
      String filename = ""; 
      if ( args.length == 1){
         if ( args[0] == "-e"){
            want_echo = true;
         }
         else {
            filename = args[0];
         }
      }
      else if ( args.length == 2){
         if ( args[0] == "-e"){
            want_echo = true;
         }
         filename = args[1];
      }
      else if ( args.length >= 3){
         out.println("Input format:edfile [-e] [filename]");
         auxlib.exit_status = auxlib.EXIT_FAILURE;
         auxlib.exit();
      }
      dllist lines = new dllist ();
      Scanner stdin = new Scanner (in);
      readfile(lines, filename);
         
      
      for (;;) {
         out.printf ("%s: ", auxlib.program_name());
         if (! stdin.hasNextLine()) break;
         String inputline = stdin.nextLine();
         if (want_echo) out.printf ("%s%n", inputline);
         if (inputline.matches ("^\\s*$")) continue;
         char command = inputline.charAt(0);
         String insertline = inputline.substring(1);
         switch (command) {
            case '#': break;
            case '$': lines.setposition(dllist.position.LAST);
                      lines.printline();
                      break;
            case '*': lines.printall();
                      break;
            case '.': lines.printline();
                      break;
            case '0': lines.setposition(dllist.position.FIRST); 
                      lines.printline();
                      break;
            case '<': lines.setposition(dllist.position.PREVIOUS);
                      lines.printline(); 
                      break;
            case '>': lines.setposition(dllist.position.FOLLOWING);
                      lines.printline();
                      break;
            case 'a': lines.insert(inputline.substring(1), 
                      dllist.position.FOLLOWING);
                      lines.printline(); 
                      break;
            case 'd': lines.delete();
                      break;
            case 'i': lines.insert(inputline.substring(1),
                      dllist.position.PREVIOUS);
                      lines.printline();
                      break;
            case 'r': readfile(lines, insertline);
                      break;
            case 'w': 
                      break;
            default : auxlib.STUB ("Print invalid command."); break;
         }
      }
      auxlib.exit ();
   }

}

