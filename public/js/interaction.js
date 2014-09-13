(function(){

var socket = io.connect('http://localhost:9001');


			socket.on('controller', function(data) {
					
					currentValue = data;		
					
			});
			
			

			socket.on('button', function(data) {
				

				if(data == 25956){
						color = 'red';
						// $(function(){
						// 	$('embed').remove();
						// 	$('body').append('<embed src=\"beat01.wav\" autostart=\"true\" hidden=\"true\" loop=\"false\">');
						// });
					}else if(data == 28535){
						color = 'yellow';
						// $(function(){
						// 	$('embed').remove();
						// 	$('body').append('<embed src=\"beat02.wav\" autostart=\"true\" hidden=\"true\" loop=\"false\">');
						// });
					}else if(data == 25966){
						color = 'green';
						// $(function(){
						// 	$('embed').remove();
						// 	$('body').append('<embed src=\"beat03.wav\" autostart=\"true\" hidden=\"true\" loop=\"false\">');
						// });					
					}else if(data == 30053){
						color = 'blue';
						// $(function(){
						// 	$('embed').remove();
						// 	$('body').append('<embed src=\"beat04.aif\" autostart=\"true\" hidden=\"true\" loop=\"false\">');
						// });

					}else if(data == 28261){
						color = 'white';
						// $(function(){
						// 	$('embed').remove();
						// 	$('body').append('<embed src=\"beat04.aif\" autostart=\"true\" hidden=\"true\" loop=\"false\">');
						// });

					}

					start = true;			

				});

})(window, window.document, Math);