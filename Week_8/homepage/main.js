document.addEventListener('DOMContentLoaded', function () { 
    let home = document.querySelector('#home-tab2');
    let profile = document.querySelector('#profile-tab2');
    let contacts = document.querySelector('#contacts-tab2');
    let projects = document.querySelector('#projects-tab2');
    home.addEventListener('click', function () { 
        window.open("index.html", "_blank")
        //location.href = "index.html";
    });
    profile.addEventListener('click', function () { 
        window.open("profile.html", "_blank")
        //location.href = "profile.html";
    });
    contacts.addEventListener('click', function () { 
        window.open("contacts.html", "_blank")
        //location.href = "contacts.html";
    });
    projects.addEventListener('click', function () { 
        window,open("projects.html", "_blank")
        //location.href = "projects.html";
        
    });
    
});