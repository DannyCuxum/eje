
package BDconec;
import java.sql.Connection;
import java.sql.DriverManager;

public class Conexion2 {
    
    Connection con;
    String url="jdbc:oracle:thin:@localhost:1521:orcl";
    String user="DANYC";
    String pass="123";
    public Connection Conectar(){
        try {
            Class.forName("oracle.jdbc.OracleDriver");
            con=DriverManager.getConnection(url,user,pass);
           
        } catch (Exception e) {
            System.out.println("error:");
            System.out.println(e);
        }      
        return con;   
    }    
}
