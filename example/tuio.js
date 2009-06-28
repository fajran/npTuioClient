
var tuio = {
	cursors: [],
	objects: [],

	_data: {},

	_cb_object_add:    function(obj) { },
	_cb_object_update: function(obj) { },
	_cb_object_remove: function(obj) { },
	_cb_cursor_add:    function(cur) { },
	_cb_cursor_update: function(cur) { },
	_cb_cursor_remove: function(cur) { },

	// Callback from the main event handler

	callback: function(type, sid, fid, x, y, angle) {
		var data;
		
		if ((type != 0) && (type != 3)) {
			data = this._data[sid];
		}
		else {
			data = {
				sid: sid,
				fid: fid
			}
			this._data[sid] = data;
		}

		data.x = x;
		data.y = y;
		
		if (type < 3) {
			data.angle = angle;
		}

		switch (type) {
			case 0: 
				this.objects.push(data);
				this._cb_object_add(data);
				break;

			case 1: 
				this._cb_object_update(data);
				break;

			case 2: 
				this.objects.splice(this.objects.indexOf(data), 1);
				this._cb_object_remove(data);
				break;

			case 3: 
				this.cursors.push(data);
				this._cb_cursor_add(data);
				break;

			case 4: 
				this._cb_cursor_update(data);
				break;

			case 5: 
				this.cursors.splice(this.cursors.indexOf(data), 1);
				this._cb_cursor_remove(data);
				break;

			default:
				break;
		}

		if ((type == 2) || (type == 5)) {
			delete this._data[sid];
		}
	},

	// Callback for the developer

	object_add:    function(f) { this._cb_object_add    = f; },
	object_update: function(f) { this._cb_object_update = f; },
	object_remove: function(f) { this._cb_object_remove = f; },
	cursor_add:    function(f) { this._cb_cursor_add    = f; },
	cursor_update: function(f) { this._cb_cursor_update = f; },
	cursor_remove: function(f) { this._cb_cursor_remove = f; },
}

function tuio_callback(type, sid, fid, x, y, angle)	{
	tuio.callback(type, sid, fid, x, y, angle);
}

