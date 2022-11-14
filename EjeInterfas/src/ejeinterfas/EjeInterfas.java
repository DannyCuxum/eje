
package ejeinterfas;
import java.sql.Connection;
import BDconec.ConexionOracle;//mi paquete
import java.sql.ResultSet;
import java.sql.Statement;




public class EjeInterfas {

    public static void main(String[] args){
        ConexionOracle nuevC = new ConexionOracle();
        String queryO="";
        //ya sestoy conectado en este punto.
        //AQUI VA LA QUERY A LA DB.
        queryO="SELECT * FROM estudiante";
        
        try{
            //System.out.println(nuevC.conn2);
            System.out.println(queryO);
            Connection cnx = nuevC.conn;
            Statement cn = cnx.createStatement(); 
            ResultSet res= cn.executeQuery(queryO);
            //en la varaible res tengo toda la tabla de informacion del resultado
            
            //para mostrarlo:
            
            while(res.next()){
                System.out.println("------------------------");
                System.out.println(res.getString("apellidos"));
                /*
                System.out.println(res.getInt("dpi"));
                System.out.println(res.getString("nombres"));
                System.out.println(res.getString("apellidos"));
                //System.out.println(res.getString("fecha_nacimiento"));
                System.out.println(res.getString("correo"));
                System.out.println(res.getInt("telefono"));
                System.out.println(res.getString("direccion"));
                System.out.println(res.getInt("creditos"));
                //System.out.println("fecha_creacion");
                System.out.println(res.getInt("id_carrera"));
                
                */
                //System.out.println(res.getInt("dpi"));
                
            }
            
        }catch(Exception e){
            System.out.println(e.getMessage());
        }
        nuevC.desconectar();
       
    }
    
}
