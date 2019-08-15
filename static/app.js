var predict_flag = false;

// Page is ready
$(document).ready(function() {
    $('#train').click(function() {
        var seq = $('#code').text();
        if (seq == "") {
            return;
        }
        $.ajax({
            type: "POST",
            url: "/api/train",
            contentType: "application/json",
            data: JSON.stringify({"seq": seq}),
            success: function(data) {
                if (data['OK']) {
                    alert("Training model updated! Ready to use");
                    $('#code').text("");
                }
            }
        })
    });

    $('#gen').click(function() {
        $.get('/api/generate', function(data) {
            $('#code').text(data['next']);
        });
    });

    $('p').keydown(function(e) {
        if (!predict_flag || e.keyCode !== 39) { return; }
        var suggest = document.getElementById("suggestion").innerHTML;
        $("#suggestion").remove();
        $("#code").text($("#code").text() + suggest);

        var p = document.getElementById("code");
        setEndOfContenteditable(p);

        predict(0);

        predict_flag = false;
    });

    $('p').keydown(predict);

    $("#code").blur(function() {
        if (predict_flag) {
            $("#suggestion").remove();
        }
    });
});

function setEndOfContenteditable(contentEditableElement)
{
    var range,selection;
    if(document.createRange)//Firefox, Chrome, Opera, Safari, IE 9+
    {
        range = document.createRange();//Create a range (a range is a like the selection but invisible)
        range.selectNodeContents(contentEditableElement);//Select the entire contents of the element with the range
        range.collapse(false);//collapse the range to the end point. false means collapse to end rather than the start
        selection = window.getSelection();//get the selection object (allows you to change selection)
        selection.removeAllRanges();//remove any selections already made
        selection.addRange(range);//make the range you have just created the visible selection
    }
    else if(document.selection)//IE 8 and lower
    { 
        range = document.body.createTextRange();//Create a range (a range is a like the selection but invisible)
        range.moveToElementText(contentEditableElement);//Select the entire contents of the element with the range
        range.collapse(false);//collapse the range to the end point. false means collapse to end rather than the start
        range.select();//Select the range (make it the visible selection
    }
}

var predict = _.debounce(function(e) {
    if (e.keyCode === 37 ||
        e.keyCode === 38 ||
        e.keyCode === 40) {
            return;
        }
    if (e.keyCode !== 900) {
        $('#suggestion').remove();
        var words = $('#code').text().split(' ');
        if (words.length < 2) { return; }
        var current = words[words.length-2] + " " + words[words.length-1];
        $.ajax({
            type: "POST",
            url: "/api/predict",
            contentType: "application/json",
            data: JSON.stringify({"seq": current}),
            success: function(data) {

                var next = data['next'];
                if (next == "" || next.substr(next.length-1, 1) == "$") {
                    return;
                }

                var sp = document.createElement('span');
                sp.id = "suggestion";
                if (current[current.length-1] != " ") {
                    sp.innerText = " ";
                }
                sp.innerText += data['next'];
                sp.setAttribute("style", "color:gray");
                document.getElementById('code').appendChild(sp);

                predict_flag = true;
            }
        })

        return;
    }
}, 250);