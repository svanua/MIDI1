
onload_page();

function add_elemets_note(name_id_parant_elemet,id_note){
    var blocks_elemets = '<label for="Vel'+id_note+'">Vel'+id_note+'</label>'+
    '<input type="number" value="0"  name="Vel'+id_note+'">'+
    '<label for="Note'+id_note+'">Note'+id_note+'</label>'+
    '<input type="number" value="0"  name="Note'+id_note+'">'+
    '<label for="Note'+id_note+'_vel'+id_note+'">Note'+id_note+'_vel'+id_note+'</label>'+
    '<input type="number" value="0"  name="Note'+id_note+'_vel'+id_note+'">'+
    '<label for="Ch_n'+id_note+'">Ch_n'+id_note+'</label>'+
    '<input type="number" value="0"  name="Ch_n'+id_note+'">'+
    '<label for="Lenght_Note_'+id_note+'">Lenght_Note_'+id_note+'</label>'+
    '<input type="number" value="0"  name="Lenght_Note_'+id_note+'">'
    document.getElementById(name_id_parant_elemet).innerHTML = blocks_elemets;
}
function add_list_profiles(name_id_parant_elemet,count_profile,active){
    
    var blocks_elemets = "";
    /*<li name="li_profile_1" class="active_profile profile_load">p1</li>
    <li name="li_profile_1" class="profile_un_load">p1</li>
    <li name="li_profile_1" class="profile_load">p1</li>
    */
    for (let i = 1; i <= count_profile; i++) {
        if (i == active) {
            blocks_elemets+='<li name="li_profile_'+i+'" class="active_profile profile_load">p'+i+'</li>';
        }
        else{
            blocks_elemets+='<li name="li_profile_'+i+'" class="profile_no_load">p'+i+'</li>';
        }
    }
    document.getElementById(name_id_parant_elemet).innerHTML = blocks_elemets;
}

function dynamic_elemenst(){
    add_list_profiles("list_profiles",16,1);
    add_elemets_note("mapping_vel1",1);
    add_elemets_note("mapping_vel2",2);
    add_elemets_note("mapping_vel3",3);
    add_elemets_note("mapping_vel4",4);
    console.log("dynamic_elemenst finish");
}

function onload_page(){
    dynamic_elemenst();
}
