Firebase.enableLogging(true);
var root = new Firebase('https://sud.firebaseio.com/');
var heading = root.child('Headings');
var data= {};
$(document).ready(function(){
	setupFirebase();
	// increment();

});


function setupFirebase() // gets json information from firebase
 {
 	heading.transaction(function(curr) {
  if (isNaN(parseFloat(curr)))
    return 1; // initialize to 1.
  else
    return curr + 1; // increment.
}, function() {
    // Once the transaction has completed, update the UI (and watch for updates).
    heading.on('value', function(snapshot) {
      // document.getElementById('contents').innerHTML = s.val();
	   var snap = snapshot.val(); // gets a snapshow view for the kson data
 		data = snap; /// assign the data to a local variable. No more calls to Firebase necessary
 		// renderTodayText(); // get the dates working.
 		console.log(data);
    });
  });

 
 }
