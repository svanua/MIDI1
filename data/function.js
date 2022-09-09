var json_profile_midi;
var index_active_li_profile =1;
var profile_midi_filename="";

onload_page();
function input_change_value(name_input){
    var index_by_profile = index_active_li_profile -1;
    json_profile_midi["array_p"][index_by_profile][name_input] = document.getElementsByName(name_input)[0].value;
}
function add_elemets_note(name_id_parant_elemet,id_note){
    var blocks_elemets = '<label for="Vel'+id_note+'">Vel'+id_note+'</label>'+
    '<input type="number" value="0"  name="Vel'+id_note+'" onchange="input_change_value('+"'Vel"+id_note+"'"+')">'+
    '<label for="Note'+id_note+'">Note'+id_note+'</label>'+
    '<input type="number" value="0"  name="Note'+id_note+'" onchange="input_change_value('+"'Note"+id_note+"'"+')">'+
    '<label for="Note'+id_note+'_vel'+id_note+'">Note'+id_note+'_vel'+id_note+'</label>'+
    '<input type="number" value="0"  name="Note'+id_note+'_vel'+id_note+'" onchange="input_change_value('+"'Note"+id_note+"_vel"+id_note+"'"+')">'+
    '<label for="Ch_n'+id_note+'">Ch_n'+id_note+'</label>'+
    '<input type="number" value="0"  name="Ch_n'+id_note+'" onchange="input_change_value('+"'Ch_n"+id_note+"'"+')">'+
    '<label for="Lenght_Note_'+id_note+'">Lenght_Note_'+id_note+'</label>'+
    '<input type="number" value="0"  name="Lenght_Note_'+id_note+'" onchange="input_change_value('+"'Lenght_Note_"+id_note+"'"+')">'
    document.getElementById(name_id_parant_elemet).innerHTML = blocks_elemets;
}
function add_list_profiles(name_id_parant_elemet,count_profile,active){
    
    var blocks_elemets = "";
    /*<li name="li_profile_1" class="active_profile profile_load">p1</li>
    <li name="li_profile_1" class="profile_un_load">p1</li>
    <li name="li_profile_1" class="profile_load">p1</li>
    */
    for (let i = 1; i <= count_profile; i++) {
        var attr_name_li ='li_profile_'+i;
        if (i == active) {
            blocks_elemets+='<li name="'+attr_name_li+'" class="active_profile profile_no_load" onclick="set_active_profile_midi('+"'"+attr_name_li+"'"+')" >p'+i+'</li>';
        }
        else{
            blocks_elemets+='<li name="'+attr_name_li+'" class="profile_no_load" onclick="set_active_profile_midi('+"'"+attr_name_li+"'"+')" >p'+i+'</li>';
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

function httpPostAsync(theUrl,str,callback){
    var xmlHttp = new XMLHttpRequest();
    //xmlHttp.setRequestHeader('Content-Type', 'application/json');
    xmlHttp.onreadystatechange = function() { 
        if ((xmlHttp.readyState == 4) && ((xmlHttp.status >= 200) && (xmlHttp.status < 300) ))
            callback(xmlHttp.responseText);            
    }
    xmlHttp.open("POST", theUrl, true); // true for asynchronous 
    xmlHttp.send(str);
}

function httpGetAsync(theUrl, callback)
{
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.onreadystatechange = function() { 
        if ((xmlHttp.readyState == 4) && (xmlHttp.status >= 200) && (xmlHttp.status < 300))
            callback(xmlHttp.responseText);
    }
    xmlHttp.open("GET", theUrl, true); // true for asynchronous 
    xmlHttp.send(null);
}

function load_profiles_srv(){
    httpGetAsync('/list_profiles',r=>{
        document.getElementById("select_list_profiles").innerHTML ='<option index="-1" disabled>Выбирете профиль</option>';
        var r_split = r.split("\n");
        var index =0;
        r_split.forEach(element => {
            console.log(element);
            if (element !="")
            {
                index++;
                if (index==1) document.getElementById("select_list_profiles").innerHTML += '<option selected index="'+index+'" >'+element+'</option>'; 
                else document.getElementById("select_list_profiles").innerHTML += '<option index="'+index+'" >'+element+'</option>'; 
            }
        });       
        })
    console.log("get_profile from Sever");
}
function show_parameters_p(index_p){
    index_p--;
    var preference = json_profile_midi["array_p"][index_p];
    console.log(preference);
    
    if ((index_p >=0) && (index_p <=15))
    {
        Object.keys(preference).forEach(st=>{
            try {
                var el = document.getElementsByName(st)[0];
                el.value = preference[st];
            }
            catch(e){   
                console.log("Param : " + st + " not find!")
                //console.log( e);
            }
        });
    }
    else{
        alert('Error index p = ' + index_p);
    }
   
}


function parse_profile_and_show(json_txt){
    json_profile_midi = JSON.parse(json_txt);
    console.log(json_profile_midi);
    try {
        show_parameters_p(1);
    } catch (error) {
        alert("Profile not load");
    }
        
}
function set_active_profile_midi(name_li_click){
    // меняем активный профаил(квадратик)
    var name_li_old = "li_profile_"+index_active_li_profile;
    document.getElementsByName(name_li_old)[0].classList.remove("active_profile");
    index_active_li_profile = name_li_click.slice(11,name_li_click.length)
    document.getElementsByName(name_li_click)[0].classList.add("active_profile");
   // меняем все параметры 
   show_parameters_p(index_active_li_profile);

}


function select_profile(file_name){
  // console.log(file_name);
  profile_midi_filename = file_name;
    // запрашиваем у веб сервера профаил
    httpGetAsync('/'+file_name,r=>{
        parse_profile_and_show(r);
        //console.log(r);
    });
}

function profile_save(){
    httpPostAsync('/profile_save?file_name='+profile_midi_filename,JSON.stringify(json_profile_midi),r=>{
        console.log(r);
    });
}
function profile_remove(){
    if (profile_midi_filename === "profile_default.json_midi") alert("Нельзя удалять фаил по умолчанию!");
    else{
        httpGetAsync('/profile_remove?file_name='+profile_midi_filename,
        r=>{

        });
    }
    
}
function profile_add(){
    var defaultText = "file_name";
    var result_file_name =  window.prompt("Введите название нового файла", defaultText);   
    result_file_name += ".json_midi"; 
    alert("Файли буде называться "+result_file_name);
    httpGetAsync('/profile_add?file_name='+result_file_name,r=>{
        console.log(r);
    });

}



function onload_page(){
    load_profiles_srv();
    dynamic_elemenst();
    select_profile("profile_default.json_midi");
    //console.log("width = "+window.screen.width+ "  height"+window.screen.height);
}


