package com.example.projetkenzasouabni;
import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class Modification extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_grade);
        EditText editcode = (EditText) findViewById(R.id.gcode);
        EditText editnom = (EditText) findViewById(R.id.gnom);
        EditText editprenom = (EditText) findViewById(R.id.gprenom);
        EditText editnote = (EditText) findViewById(R.id.notecc);
        EditText editex = (EditText) findViewById(R.id.noteex);
        Button btnEnregistrer = findViewById(R.id.enregistrement);
        DataBaseHandler db = new DataBaseHandler(Modification.this);

        editcode.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                editcode.setOnFocusChangeListener(new View.OnFocusChangeListener() {
                    @Override
                    public void onFocusChange(View v, boolean hasFocus) {
                        Etudiant e
                        e.setCode(editcode.getText().toString());
                        Etudiant e1 = db.searchEtudiant(e);
                        if (e1 != null) {
                            editnom.setText(e1.getNom());
                            editprenom.setText(e1.getPrenom());
                            editnote.setText(e1.getNoteds());
                            editex.setText(e1.getNoteexamen());
                        } else
                            Toast.makeText(Modification.this, "Étudiant(e) introuvable", Toast.LENGTH_LONG).show();
                    }
                });

            }

        });
        btnEnregistrer.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Etudiant e = new Etudiant(
                        editnom.getText().toString(),
                        editprenom.getText().toString(),
                        (Integer.parseInt(editnote.getText().toString())),
                        (Integer.parseInt(editex.getText().toString()))
                );
                e.setCode(editcode.getText().toString());
                int r = db.updateEtudiant(e);
                if (r != -1)
                    Toast.makeText(Modification.this, "Mise à jour avec succès ", Toast.LENGTH_LONG).show();
                else
                    Toast.makeText(Modification.this, "Problème dans la mise à jour ", Toast.LENGTH_LONG).show();
            }
        });
    }
}

 = new Etudiant();