import numpy as np
import numpy.linalg as la
import scipy.linalg as sla
import matplotlib as mpl
import matplotlib.pyplot as plt
from matplotlib.offsetbox import OffsetImage, AnnotationBbox
import mplcursors
import math
import csv
import random
import PySimpleGUI as sg

test_time = "36$4$5"

def convert_to_time(time_to_convert):
	to_return = ""
	list_of_times = []
	temp_str = ""
	for i in range(0, len(time_to_convert)):
		if time_to_convert[i] == '$':
			list_of_times.append(temp_str)
			temp_str = ""
		else:
			temp_str += time_to_convert[i]
	if len(temp_str) > 0:
		list_of_times.append(temp_str)
	list_of_times = list_of_times[::-1]
	to_return = str(list_of_times[0]) + " hours; " + str(list_of_times[1]) + " minutes; " + str(list_of_times[2]) + " seconds"
	return (to_return, list_of_times[3])

def read_csv(filename, delimeter):
	stop = 1
	file_contents = []
	file = open(filename)
	csvreader = csv.reader(file)
	for row in csvreader:
		file_contents.append(row)
	file.close()

	to_return = []
	for i in range(0, len(file_contents)):
		for j in range(0, len(file_contents[i])):
			split_list = file_contents[i][j].split(delimeter)

			for item in split_list:
				item_new = item.strip()
				if (len(item_new) > 0) and (item_new not in to_return):
					to_return.append(item_new)
	return to_return

# list_test = read_csv('username.csv', ';')
# print(list_test)

def convert_to_x_array(pt1, pt2):
	to_return = [pt1[0], pt2[0]]
	return to_return

def convert_to_y_array(pt1, pt2):
	to_return = [pt1[1], pt2[1]]
	return to_return

def convert_to_regular_list(to_convert):
	return (to_convert[0], to_convert[1])

def dict_count(dict_to_iterate_over, key):
	count = 0
	for i in dict_to_iterate_over:
		if (i == key) or ( (np.floor(i[0]) == np.floor(key[0])) and (np.floor(i[1]) == np.floor(key[1])) ) or ( (np.ceil(i[0]) == np.ceil(key[0])) and (np.ceil(i[1]) == np.ceil(key[1])) ):
			count += 1
	return count

def tolerance(to_test, to_return):
	tolerance = 5
	closest_key = min(to_return.keys(), key=lambda x: ((x[0]-to_test[0])**2 + (x[1]-to_test[1])**2)**0.5 if ((x[0]-to_test[0])**2 + (x[1]-to_test[1])**2)**0.5 <= tolerance else float('inf'))
	return closest_key

def euclidean_distance(point1, point2):
	x1, y1 = point1
	x2, y2 = point2
	return math.sqrt((x2 - x1) ** 2 + (y2 - y1) ** 2)

def plot_line(axis, pts):
	random_colors = ['bo', 'go', 'ro', 'co', 'mo', 'yo', 'ko', 'wo']
	x_values = convert_to_x_array(pts[0], pts[1])
	y_values = convert_to_y_array(pts[0], pts[1])
	axis.plot(x_values, y_values, random.choice(random_colors), linestyle="--")

def underground_plot_line(axis, pts):
	x_values = convert_to_x_array(pts[0], pts[1])
	y_values = convert_to_y_array(pts[0], pts[1])
	axis.plot(x_values, y_values, 'bo', linestyle="--")

def fast_travel_plot_line(axis, pts):
	x_values = convert_to_x_array(pts[0], pts[1])
	y_values = convert_to_y_array(pts[0], pts[1])
	axis.plot(x_values, y_values, 'wo', linestyle="--")

def plot_path(axis, places, bosses_to_point, points_to_bosses):
	for i in range(1, len(places)-1):
		first_boss = bosses_to_point[places[i]]
		second_boss = bosses_to_point[places[i + 1]]
		pts_to_plot = [convert_to_regular_list(first_boss), convert_to_regular_list(second_boss)]
		plot_line(axis, pts_to_plot)

def final_product(csv_contents):

	### UNCOMMENT THIS LINE WHEN WE'RE READY TO READ IN CSV

	# csv_contents = read_csv(filename, delimeter)

	### UNCOMMENT THIS LINE WHEN WE'RE READY TO READ IN CSV

	first_step = np.array([249.5, 482.1])
	gate_front = np.array([236.7, 457.3])
	third_church = np.array([312.6, 447.7])
	dectus_height = np.array([319.1, 487.0])
	margit = np.array([224.1, 455.1])
	godrick = np.array([210.6, 430.8])
	ancestral_woods = np.array([302.8, 473.4])
	finger_slayer = np.array([290.2, 467.6])
	regal_ancestor = np.array([305.9, 487.9])
	valiant_gargoyles = np.array([333.3, 460.1])
	liurnia_highway_south = np.array([206.6, 412.4])
	liurnia_tower = np.array([227.9, 341.8])
	albanaric_medallion = np.array([117.4, 388.5])
	smaurag = np.array([109.5, 333.1])
	ria_south = np.array([137.3, 336.7])
	ria_north = np.array([127.4, 315.5])
	cuckoo_church = np.array([133.6, 335.0])
	ria_abductor = np.array([133.2, 329.7])
	red_wolf = np.array([131.0, 331.3])
	rennala = np.array([127.3, 325.1])
	caria_gate = np.array([138.1, 257.2])
	royal_kinght_loretta = np.array([128.9, 239.7])
	ranni = np.array([116.9, 239.4])
	dectus_lift = np.array([182.2, 249.0])
	ansel_main = np.array([187.7, 317.7])
	astel = np.array([88.1, 405.0])
	draconic_tree_sentinel = np.array([307.1, 215.4])
	godfrey_golden_shade = np.array([292.9, 246.5])
	morgott = np.array([308.4, 249.9])
	deep_root_main = np.array([321.6, 246.1])
	fia_champ = np.array([302.1, 200.5])
	fordysax = np.array([302.1, 200.5])
	gurranq = np.array([414.5, 373.4])
	dectus_pharoth = np.array([428.8, 404.7])
	radahn = np.array([422.8, 447.1])
	abductor_duo = np.array([176.9, 204.9])
	godskin_noble = np.array([146.2, 190.7])
	rykard = np.array([156.7, 195.2])
	rold = np.array([371.3, 203.9])
	mountain_tops_fork = np.array([430.8, 126.6])
	nial = np.array([410.3, 114.8])
	fire_giant = np.array([430.2, 207.0])
	godskin_duo = np.array([562.6, 297.3])
	great_bridge = np.array([580.3, 293.1])
	maliketh = np.array([586.01, 295.86])
	placidusax = np.array([575.9, 302.3])
	gideon = np.array([292.9, 239.5])
	gofrey = np.array([308.4, 242.9])
	radagon_elden_beast = np.array([320.72, 266.86])
	mohg_palace = np.array([431.7, 454.3])
	mohg = np.array([414.8, 458.6])
	snowfield_inner = np.array([363.8, 153,6])
	snowfield_mohg_tele = np.array([335.7, 159.8])
	haligtree_canopy = np.array([383.2, 69.4])
	loretta_haligtree = np.array([390.6, 61.8])
	malenia = np.array([379, 57])

	bosses_to_point = {"firstStep" : first_step, "gatefront" : gate_front, "thirdChurch" : third_church, "dectusHaight" : dectus_height, "margit" : margit, "godrick" : godrick, "ancestralWoods" : ancestral_woods, "fingerslayer" : finger_slayer, "regalAncestor" : regal_ancestor, "valiantGargs" : valiant_gargoyles, "liurniaHighwaySouth" : liurnia_highway_south, "liurniaTower" : liurnia_tower, "albinauricMedalion" : albanaric_medallion, "smarag" : smaurag, "rayaSouth" : ria_south, "rayaNorth" : ria_north, "cuckooChurch" : cuckoo_church, "rayaAbuctor" : ria_abductor, "redWolf" : red_wolf, "rennala" : rennala, "cariaGate" : caria_gate, "royalKnightLoretta" : royal_kinght_loretta, "ranni" : ranni, "dectus" : dectus_lift, "ainselMain" : ansel_main, "astel" : astel, "draconicTreeSentinel" : draconic_tree_sentinel, "godfreyGoldenShade" : godfrey_golden_shade, "morgott" : morgott, "deeprootMain" : deep_root_main, "fiasChamps" : fia_champ, "fortissax" : fordysax, "gurranq" : gurranq, "dectusFaroth" : dectus_pharoth, "radahn" : radahn, "abductorDuo" : abductor_duo, "godskinNoble" : godskin_noble, "rykard" : rykard, "rold" : rold, "mountaintopsFork" : mountain_tops_fork, "niallMedalion" : nial, "fireGiant" : fire_giant, "godskinDuo" : godskin_duo, "greatBridge" : great_bridge, "maliketh" : maliketh, "placidusax" : placidusax, "gideon" : gideon, "godfrey" : gofrey, "radagonAndEldenBeast" : radagon_elden_beast, "mohgwynPalace" : mohg_palace, "mohg" : mohg, "snowfieldInner" : snowfield_inner, "snowfieldMohgTele" : snowfield_mohg_tele, "haligtreeCanopy" : haligtree_canopy , "lorettaHaligtree" : loretta_haligtree , "malenia" : malenia}
	points_to_bosses = {convert_to_regular_list(first_step): "First Step", convert_to_regular_list(gate_front) : "Gate Front", convert_to_regular_list(third_church) : "Third Church of Marika", convert_to_regular_list(dectus_height) : "Fort Haight", convert_to_regular_list(margit) : "Margit, the Fell Omen", convert_to_regular_list(godrick) : "Godrick the Grafted", convert_to_regular_list(ancestral_woods) : "Ancestral Woods", convert_to_regular_list(finger_slayer) : "Fingerslayer Blade", convert_to_regular_list(regal_ancestor) : "Regal Ancestor", convert_to_regular_list(valiant_gargoyles) : "Valiant Gargoyles", convert_to_regular_list(liurnia_highway_south) : "Liurnia Highway South", convert_to_regular_list(liurnia_tower) : "Liurnia Tower", convert_to_regular_list(albanaric_medallion) : "Albanauric Medallion", convert_to_regular_list(smaurag) : "Smarag", convert_to_regular_list(ria_south) : "Raya Lucaria South", convert_to_regular_list(ria_north) : "Raya Lucaria North", convert_to_regular_list(cuckoo_church) : "Church of the Cuckoo", convert_to_regular_list(ria_abductor) : "Raya Abductor", convert_to_regular_list(red_wolf) : "Red Wolf of Radagon", convert_to_regular_list(rennala) : "Rennala, Queen of the Full Moon", convert_to_regular_list(caria_gate) : "Caria Manor", convert_to_regular_list(royal_kinght_loretta) : "Royal Knight Loretta", convert_to_regular_list(ranni) : "Ranni", convert_to_regular_list(dectus_lift) : "Grand Lift of Dectus", convert_to_regular_list(ansel_main) : "Ainsel River Main", convert_to_regular_list(astel) : "Astel, Naturalborn of the Void", convert_to_regular_list(draconic_tree_sentinel) : "Draconic Tree Sentinel", convert_to_regular_list(godfrey_golden_shade) : "Godfrey (Golden Shade)", convert_to_regular_list(morgott) : "Morgott, the Omen King", convert_to_regular_list(deep_root_main) : "Deeproot Depths", convert_to_regular_list(fia_champ) : "Fia's Champions", convert_to_regular_list(fordysax) : "Lichdragon Fortissax", convert_to_regular_list(gurranq) : "Gurranq", convert_to_regular_list(dectus_pharoth) : "Fort Faroth", convert_to_regular_list(radahn) : "Starscourge Radahn", convert_to_regular_list(abductor_duo) : "Abductor Duo", convert_to_regular_list(godskin_noble) : "Godskin Noble", convert_to_regular_list(rykard) : "Rykard, Lord of Blasphemy", convert_to_regular_list(rold) : "Grand Lift of Rold", convert_to_regular_list(mountain_tops_fork) : "Mountaintops of the Giants", convert_to_regular_list(nial) : "Commander Niall", convert_to_regular_list(fire_giant) : "Fire Giant", convert_to_regular_list(godskin_duo) : "Godskin Duo", convert_to_regular_list(great_bridge) : "Great Bridge", convert_to_regular_list(maliketh) : "Maliketh, the Black Blade", convert_to_regular_list(placidusax) : "Dragonlord Placidusax", convert_to_regular_list(gideon) : "Gideon Ofnir", convert_to_regular_list(gofrey) : "Godfrey, the First Elden Lord", convert_to_regular_list(radagon_elden_beast) : "Radagon and Elden Beast", convert_to_regular_list(mohg_palace) : "Mohgwyn Palace", convert_to_regular_list(mohg) : "Mohg, Lord of Blood", convert_to_regular_list(snowfield_inner) : "Consecrated Snowfield", convert_to_regular_list(snowfield_mohg_tele) : "Snowfield Mohg Teleporter", convert_to_regular_list(haligtree_canopy) : "Miquella's Haligtree" , convert_to_regular_list(loretta_haligtree) : "Loretta, Knight of the Haligtree", convert_to_regular_list(malenia) : "Malenia, Goddess of Rot"}


	places = ["First Step", "Gate Front", "Third Church of Marika", "Fort Haight", "Margit, the Fell Omen", "Godrick the Grafted", "Ancestral Woods", "Fingerslayer Blade", "Regal Ancestor", "Valiant Gargoyles", "Liurnia Highway South", "Liurnia Tower", "Albanauric Medallion", "Smarag", "Raya Lucaria South", "Raya Lucaria North", "Church of the Cuckoo", "Raya Abductor", "Red Wolf of Radagon", "Rennala, Queen of the Full Moon", "Caria Manor", "Royal Knight Loretta", "Ranni", "Grand Lift of Dectus", "Ainsel River Main", "Astel, Naturalborn of the Void", "Draconic Tree Sentinel", "Godfrey (Golden Shade)", "Morgott, the Omen King", "Deeproot Depths", "Fia's Champions", "Lichdragon Fortissax", "Gurranq", "Fort Faroth", "Starscourge Radahn", "Abductor Duo", "Godskin Noble", "Rykard, Lord of Blasphemy", "Grand Lift of Rold", "Mountaintops of the Giants", "Commander Niall", "Fire Giant", "Godskin Duo", "Great Bridge", "Maliketh, the Black Blade", "Dragonlord Placidusax", "Gideon Ofnir", "Godfrey, the First Elden Lord", "Radagon and Elden Beast", "Mohgwyn Palace", "Mohg, Lord of Blood", "Consecrated Snowfield", "Snowfield Mohg Teleporter", "Miquella's Haligtree", "Loretta, Knight of the Haligtree", "Malenia, Goddess of Rot"]



	bosses = np.array([ [first_step[0], first_step[1]], [gate_front[0], gate_front[1]], [third_church[0], third_church[1]], [dectus_height[0], dectus_height[1]], [margit[0], margit[1]], [godrick[0], godrick[1]], [ancestral_woods[0], ancestral_woods[1]], [finger_slayer[0], finger_slayer[1]], [regal_ancestor[0], regal_ancestor[1]], [valiant_gargoyles[0], valiant_gargoyles[1]], [liurnia_highway_south[0], liurnia_highway_south[1]], [liurnia_tower[0], liurnia_tower[1]], [albanaric_medallion[0], albanaric_medallion[1]], [smaurag[0], smaurag[1]], [ria_south[0], ria_south[1]], [ria_north[0], ria_north[1]], [cuckoo_church[0], cuckoo_church[1]], [ria_abductor[0], ria_abductor[1]], [red_wolf[0], red_wolf[1]], [rennala[0], rennala[1]], [caria_gate[0], caria_gate[1]], [royal_kinght_loretta[0], royal_kinght_loretta[1]], [ranni[0], ranni[1]], [dectus_lift[0], dectus_lift[1]], [ansel_main[0], ansel_main[1]], [astel[0], astel[1]], [draconic_tree_sentinel[0], draconic_tree_sentinel[1]], [godfrey_golden_shade[0], godfrey_golden_shade[1]], [morgott[0], morgott[1]], [deep_root_main[0], deep_root_main[1]], [fia_champ[0], fia_champ[1]], [fordysax[0], fordysax[1]], [gurranq[0], gurranq[1]], [dectus_pharoth[0], dectus_pharoth[1]], [radahn[0], radahn[1]], [abductor_duo[0], abductor_duo[1]], [godskin_noble[0], godskin_noble[1]], [rykard[0], rykard[1]], [rold[0], rold[1]], [mountain_tops_fork[0], mountain_tops_fork[1]], [nial[0], nial[1]], [fire_giant[0], fire_giant[1]], [godskin_duo[0], godskin_duo[1]], [great_bridge[0], great_bridge[1]], [maliketh[0], maliketh[1]], [placidusax[0], placidusax[1]], [gideon[0], gideon[1]], [gofrey[0], gofrey[1]], [radagon_elden_beast[0], radagon_elden_beast[1]], [mohg_palace[0], mohg_palace[1]], [mohg[0], mohg[1]], [snowfield_inner[0], snowfield_inner[1]], [snowfield_mohg_tele[0], snowfield_mohg_tele[1]], [haligtree_canopy[0], haligtree_canopy[1]], [loretta_haligtree[0], loretta_haligtree[1]], [malenia[0], malenia[1]]])
	x_bosses = bosses[:,0]
	y_bosses = bosses[:,1]
	### EXTRA ADDED BENEFITS

	# USING AN IMAGE FOR THE POINTS
	# test_path, attributes = svg2paths('test.svg')
	# test_marker = parse_path(attributes[0]['d'])
	# test_marker.vertices -= test_marker.vertices.mean(axis=0)
	# test_marker = test_marker.transformed(mpl.transforms.Affine2D().rotate_deg(180))
	# test_marker = test_marker.transformed(mpl.transforms.Affine2D().scale(-1,1))
	# END USING AN IMAGE FOR THE POINTS


	# ANNOTATING ALL OF THE POINTS INDIVIDUALLY
	# for x in range(0, len(places)):
	# 	label = places[x]
	# 	x_coord = bosses[x][0]
	# 	y_coord = bosses[x][1]
	# 	plt.annotate(label, # this is the value which we want to label (text)
	# 	             (x_coord,y_coord), # x and y is the points location where we have to label
	# 	             textcoords="offset points",
	# 	             xytext=(0,10), # this for the distance between the points
	# 	             # and the text label
	# 	             ha='center',
	# 	             arrowprops=dict(arrowstyle="->", color='black'), fontsize=5, color='white')
	# END ANNOTATING ALL OF THE POINTS INDIVIDUALLY

	# START CREATING A LINE
	# x_values = convert_to_x_array(pts[0], pts[1])
	# y_values = convert_to_y_array(pts[0], pts[1])
	# plt.plot(x_values, y_values, 'bo', linestyle="--")
	# END CREATING A LINE


	### PLOT LINE FUNCTION EXAMPLE USAGE: 

	# pts_test = [convert_to_regular_list(malenia), convert_to_regular_list(godrick)]
	# plot_line(ax, pts_test)

	### END PLOT LINE FUNCTION EXAMPLE USAGE: 


	### END EXTRA ADDED BENEFITS

	pts = np.array([[289, 410], [312, 242], [598, 112], [548, 142]])
	x_values = pts[:,0]
	y_values = pts[:,1]

	img = plt.imread("map.jpg")
	fig, ax = plt.subplots()
	ax.imshow(img)
	ax.plot(x_bosses, y_bosses, 'o', color='yellow', markersize=5)


	### UNCOMMENT THIS LINE WHEN WE'RE READY TO READ IN CSV

	plot_path(ax, csv_contents, bosses_to_point, points_to_bosses)
	visited = []
	for x in range(1, len(csv_contents)):
		boss = bosses_to_point[csv_contents[x]]
		if (points_to_bosses[convert_to_regular_list(boss)] not in visited):
			print(points_to_bosses[convert_to_regular_list(boss)])
			points_to_bosses[convert_to_regular_list(boss)] = points_to_bosses[convert_to_regular_list(boss)] + ", Stop: " + str(x)
			visited.append(points_to_bosses[convert_to_regular_list(boss)])


	# pts_test = [convert_to_regular_list(malenia), convert_to_regular_list(godrick)]
	# plot_line(ax, pts_test)
	### UNCOMMENT THIS LINE WHEN WE'RE READY TO READ IN CSV


	cursors = mplcursors.cursor(hover=True, highlight=False)
	@cursors.connect("add")
	def _(sel):
		x, y = sel.target
		test_tuple = (x, y)
		if tolerance(test_tuple, points_to_bosses) in points_to_bosses and euclidean_distance(test_tuple, tolerance(test_tuple, points_to_bosses)) < 10:
			sel.annotation.set(position=(sel.target[0],sel.target[1]))
			# Note: Needs to be set separately due to matplotlib/matplotlib#8956.
			sel.annotation.get_bbox_patch().set(fc="lightgrey")
			sel.annotation.arrow_patch.set(arrowstyle="simple", fc="white", alpha=0)
			sel.annotation.set_text(points_to_bosses[tolerance(test_tuple, points_to_bosses)])
		else:
			sel.annotation.set_visible(False)

	test_title = 'Time for this run (' + convert_to_time(csv_contents[0])[1] + '): ' + convert_to_time(csv_contents[0])[0]
	ax.set_title(test_title)

	# plt.show()





# sg.theme('DarkAmber')

# layout = [  [sg.Text('Input the filename of the CSV'), sg.InputText()],
#             [sg.Text('Input the delimeter used in the CSV'), sg.InputText()],
#             [sg.Button('Ok'), sg.Button('Cancel')] ]


# window = sg.Window('Plotter', layout)

# while True:
# 	event, values = window.read()
# 	if event == sg.WIN_CLOSED or event == 'Cancel':
# 		break
# 	if event == 'Ok':
# 		filename = values[0]
# 		delimeter = values[1]
# 		final_product(filename, delimeter)
# 		break

# window.close()


if __name__ == '__main__':
	layout = [[sg.Text('Select Output CSV File from Program:')],
	          [sg.Input(key='_FILEBROWSE_', enable_events=True, visible=False), sg.FileBrowse()],
	          [sg.OK(), sg.Cancel()]]

	# Create the window
	window = sg.Window('File Browser', layout)

	# Start an event loop to process events
	while True:
		event, values = window.read()

		# Handle events
		if event == sg.WINDOW_CLOSED or event == 'Cancel':
			break
		elif event == 'OK':
			# Get the path of the selected file
			filepath = values['_FILEBROWSE_']
			delimeter = ','
			# Read in the contents of the file
			csv_contents = read_csv(filepath, delimeter)
			figure = final_product(csv_contents)
			plt.show()
			break

	        # Display the file contents in a popup

# filename = 'dijkstras-output.csv'
# delimeter = ','
# final_product(filename, delimeter)
