
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class driverJNI {
	
	static {
	      System.loadLibrary("bzip2"); // hello.dll (Windows) or libhello.so (Unixes)
	   }
	public native boolean compress(String src,String dest,int levelOfCompression);
	 public native boolean decompress(String src,String dest,int levelOfDecompression);
	public static void main(String[] args) {
		Boolean CONFIRMATION = null;
		String src="";
		String dest="";
		Scanner sc=new Scanner(System.in);
		System.out.println("Options \n 1)For Compression \n 2)For Decompression");
		String i=sc.next();
		int level = 0;
		if(i.equals("1"))
			{
			
			System.out.println("Selected Compression");
			
			System.out.println("Enter Level Of Compression from 1-9");
			level=sc.nextInt();
			
			System.out.println("Enter a Source Path");
			while(src.isEmpty()) {
				src=sc.nextLine();
			}
			System.out.println("Enter The Destination path");
			while(dest.isEmpty())
			dest=sc.nextLine();
			try {
				CONFIRMATION=compression(src, dest,level);
			} catch (FileNotFoundException e) {
				// TODO Auto-generated catch block
				System.out.println("File Not FOund");
			}sc.close();
			}
		if(i.equals("2")){
			System.out.println("Selected Decompression");
			System.out.println("Enter Level Of DecCompression from 1-9");
			level=sc.nextInt();
			System.out.println("Enter a Source Path");
			while(src.isEmpty()) {
				src=sc.nextLine();
			}
			System.out.println("Enter The Destination path");
			while(dest.isEmpty())
			dest=sc.nextLine();
			try {
				CONFIRMATION=decompression(src, dest,level);
			} catch (FileNotFoundException e) {
				// TODO Auto-generated catch block
				System.out.println("File Not FOund");
			}
		}sc.close();
		if(CONFIRMATION) System.out.println("Successfull");
		else System.out.println("Failure");
		

	}
	public static Boolean compression(String src,String dest,int level) throws FileNotFoundException{
		driverJNI comp=new driverJNI();
		Boolean CONFIRMATION;
		if(new File(src).exists()&&new File(dest).exists()){
			System.out.println("File Exists");
			CONFIRMATION=comp.compress(src,dest,level);
			
		}
		else throw new FileNotFoundException();
		
		//comp.compress(src,dest);
		return CONFIRMATION;
		
	}
	   public static Boolean decompression(String src,String dest,int level) throws FileNotFoundException{
		   driverJNI decomp=new driverJNI();
		   Boolean CONFIRMATION;
		   if(new File(src).exists()&&new File(dest).exists()){
			System.out.println("File Exists");
			CONFIRMATION=decomp.decompress(src,dest,level);
			
		}
		else throw new FileNotFoundException();
		
		//comp.compress(src,dest);
		return CONFIRMATION;
		
	}

}
